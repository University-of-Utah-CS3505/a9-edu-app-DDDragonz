#include "MW.h"
#include "ui_MW.h"
#include "contactlistener.h"
#include <QDebug>

MW::MW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MW)
    , world(new b2World(b2Vec2(0.0f, -10.0f)))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    windowWidth = this->width();
    windowHeight = this->height() - 50;

    chemA = new Chemical(0, Qt::yellow);
    chemB = new Chemical(1, Qt::green);

    connect(timer,
            &QTimer::timeout,
            this,
            &MW::Update);


    connect(ui->reset,
            &QPushButton::clicked,
            this,
            &MW::resetScene);

    world->SetContactListener(&contact);
    createScene();
}

void MW::createBorder()
{
    //Define body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(0, 0);
    b2Body* body = world->CreateBody(&bodyDef);
    b2EdgeShape edge;

    // Bottom border
    edge.Set(b2Vec2(0, 0), b2Vec2(windowWidth / SCALE, 0));
    body->CreateFixture(&edge, 0);

    // Left border
    edge.Set(b2Vec2(0, 0), b2Vec2(0, windowHeight / SCALE));
    body->CreateFixture(&edge, 0);

    // Top border
    edge.Set(b2Vec2(0, windowHeight / SCALE), b2Vec2(windowWidth / SCALE, windowHeight / SCALE));
    body->CreateFixture(&edge, 0);

    // Right border
    edge.Set(b2Vec2(windowWidth / SCALE, 0), b2Vec2(windowWidth / SCALE, windowHeight / SCALE));
    body->CreateFixture(&edge, 0);
}

void MW::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for (b2Body* body = world->GetBodyList(); body != 0; body = body->GetNext())
    {
        for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            b2Shape* shape = fixture->GetShape();
            if (shape->GetType() == b2Shape::e_edge)
            {
                drawEdge(painter, body, (b2EdgeShape*)shape);
            }
            else if (shape->GetType() == b2Shape::e_circle)
            {
                Chemical c = *static_cast<Chemical*>(body->GetUserData());
                drawCircle(painter, body, (b2CircleShape*)shape, c.s_color);
            }
            else if (shape->GetType() == b2Shape::e_polygon)
            {
                drawPolygon(painter, body, (b2PolygonShape*)shape);
            }
        }
    }
}
void MW::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        b2Vec2 pos(event->pos().x() / SCALE, (windowHeight - event->pos().y()) / SCALE);
        b2Vec2 velocity = pos - vial->GetPosition();
        float velocityScale = 3.0f; //Changeable
        velocity *= velocityScale;
        vial->SetLinearVelocity(velocity);
        update();
    }
}

void MW::createVial()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    //bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.position.Set(windowWidth  / 4 / SCALE, windowHeight / 3 / SCALE);
    vial = world->CreateBody(&bodyDef);

    vial->SetLinearDamping(3.0f);
    vial->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-1.0f, -3.0f); //bottom-left
    vertices[1].Set(-1.0f, 3.0f); //top-left
    vertices[2].Set(1.0f, 3.0f); //top-right
    vertices[3].Set(1.0f, -3.0f); //bottom-right

    createWall(vial, vertices[0], vertices[1]); // Left wall
    createWall(vial, vertices[2], vertices[3]); // Right wall
    createWall(vial, vertices[0], vertices[3]); // Bottom wall
}

void MW::createStaticVial()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.position.Set(3*windowWidth  / 4 / SCALE, windowHeight / 3 / SCALE);
    staticVial = world->CreateBody(&bodyDef);

    staticVial->SetLinearDamping(3.0f);
    staticVial->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-1.0f, -3.0f); //bottom-left
    vertices[1].Set(-1.0f, 3.0f); //top-left
    vertices[2].Set(1.0f, 3.0f); //top-right
    vertices[3].Set(1.0f, -3.0f); //bottom-right

    createWall(staticVial, vertices[0], vertices[1]); // Left wall
    createWall(staticVial, vertices[2], vertices[3]); // Right wall
    createWall(staticVial, vertices[0], vertices[3]); // Bottom wall
}

void MW::SpawnBox()
{
    // Define a body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody; // Set the body to be dynamic
    bodyDef.position.Set(windowWidth  / 2 / SCALE, windowHeight / 2 / SCALE);
    b2Body *body = world->CreateBody(&bodyDef);

    // Assign a rectangular shape to the body
    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.5f, 1.0f);

    // Define fixture
    b2FixtureDef fixture;
    fixture.shape = &boxShape; // Assign shape to fixture
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.restitution = 0.3f;

    // Attach the fixture to the body
    body->CreateFixture(&fixture);
}

void MW::SpawnCircle(Chemical* chemical, b2Body* vial, float offset)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 vialPosition = vial->GetWorldCenter();
    bodyDef.position.Set(vialPosition.x, vialPosition.y + offset);
    b2Body* particle = world->CreateBody(&bodyDef);
    particle->SetUserData((void*)chemical);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.01f;
    particle->CreateFixture(&fixtureDef);
}

void MW::createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2)
{
    b2PolygonShape wall;
    float thickness = 0.1f;
    b2Vec2 direction = vertex2 - vertex1;
    b2Vec2 offset(direction.y, -direction.x);
    offset.Normalize();
    offset *= thickness / 2;
    b2Vec2 vertices[4] = {vertex1 - offset, vertex2 - offset, vertex2 + offset, vertex1 + offset};
    wall.Set(vertices, 4);

    b2FixtureDef fixture;
    fixture.shape = &wall;
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.restitution = 0.3f;
    body->CreateFixture(&fixture);
}

void MW::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Q:
        vial->SetAngularVelocity(-1);
        break;
    case Qt::Key_E:
        vial->SetAngularVelocity(1);
        break;
    case Qt::Key_W:
        vial->ApplyLinearImpulse(b2Vec2(0.0f, 10.0f), vial->GetWorldCenter(), true);
        break;
    case Qt::Key_A:
        vial->ApplyLinearImpulse(b2Vec2(-10.0f, 0.0f), vial->GetWorldCenter(), true);
        break;
    case Qt::Key_S:
        vial->ApplyLinearImpulse(b2Vec2(0.0f, -10.0f), vial->GetWorldCenter(), true);
        break;
    case Qt::Key_D:
        vial->ApplyLinearImpulse(b2Vec2(10.0f, 0.0f), vial->GetWorldCenter(), true);
        break;
    }

    update();
    b2Vec2 vialPosition = vial->GetPosition();
    float32 vialAngle = vial->GetAngle();
    qDebug() << "Vial Position: (" << vialPosition.x << ", " << vialPosition.y << ")" << "Vial Angle: " << vialAngle;
}

void MW::createScene()
{
    SpawnBox();
    createVial();
    createStaticVial();

    for (int i = 0; i < 99; i++)
    {
        SpawnCircle(chemA, vial, i/50);
    }

    for (int i = 0; i < 99; i++)
    {
        SpawnCircle(chemB, staticVial, i/50);
    }

    createBorder();
    update();
    timer->start(1000 / 60);
}

void MW::resetScene()
{
    timer->stop();
    for (b2Body* body = world->GetBodyList(); body != 0; body = body->GetNext())
    {
        world->DestroyBody(body);
    }
    world->Step(1/60.f, 8, 3); // make sure everything is deleted
    b2Vec2 gravity(0.0f, -10.0f);
    if(world != nullptr)
    {
        delete world;
        world = nullptr;
    }
    world = new b2World(gravity);
    chemA->s_color = Qt::yellow;
    chemB->s_color = Qt::green;
    world->SetContactListener(&contact);
    createScene();
}

void MW::drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge)
{
    QPen pen(Qt::black);
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    QPointF v1 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex1));
    QPointF v2 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex2));
    painter.drawLine(v1, v2);
}

void MW::drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon)
{
    QPen pen(Qt::black);
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    QPolygonF qpolygon;
    for (int32 i = 0; i < polygon->m_count; ++i)
    {
        QPointF v = convertCoordsBox2DToQt(body->GetWorldPoint(polygon->m_vertices[i]));
        qpolygon.append(v);
    }
    painter.drawPolygon(qpolygon);
}

void MW::drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color)
{
    QPen pen(color);
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(color);
    QPointF position = convertCoordsBox2DToQt(body->GetPosition());
    painter.drawEllipse(position, circle->m_radius * SCALE, circle->m_radius * SCALE);
}

QPointF MW::convertCoordsBox2DToQt(b2Vec2 vec)
{
    vec.x *= SCALE;
    vec.y = windowHeight - vec.y * SCALE;
    return QPointF(vec.x, vec.y);
}

void MW::Update()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    vial->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    world->Step(timeStep, velocityIterations, positionIterations);
    update();
    vial->SetLinearVelocity(b2Vec2(0,0));
}

MW::~MW()
{
    delete ui;
    delete timer;
    delete world;
}
