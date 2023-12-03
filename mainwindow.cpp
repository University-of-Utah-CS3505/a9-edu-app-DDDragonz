#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactlistener.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(new b2World(b2Vec2(0.0f, -10.0f)))
    , timer(new QTimer(this))
    , chemA()
    , chemB()
{
    ui->setupUi(this);
    windowWidth = this->width();
    // qDebug() << windowWidth;
    windowHeight = this->height() - 50;

    connect(timer,
            &QTimer::timeout,
            this,
            &MainWindow::Update);


    connect(ui->reset,
            &QPushButton::clicked,
            this,
            &MainWindow::resetScene);

    for(int i = 0; i < 100; i++)
    {
        chemA[i] = Chemical(0, Qt::yellow, false);
    }

    for(int i = 0; i < 100; i++)
    {
        chemB[i] = Chemical(1, Qt::green, false);
    }

    world->SetContactListener(&contact);

    createScene();
}

void MainWindow::createBorder()
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

void MainWindow::paintEvent(QPaintEvent*)
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
                void* e = body->GetUserData();
                if(e)
                {
                    Chemical c = *static_cast<Chemical*>(body->GetUserData());
                    drawCircle(painter, body, (b2CircleShape*)shape, c.s_color);
                }
                else
                {
                    drawCircle(painter, body, (b2CircleShape*)shape, Qt::white);
                }
            }
            else if (shape->GetType() == b2Shape::e_polygon)
            {
                drawPolygon(painter, body, (b2PolygonShape*)shape);
            }
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
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

void MainWindow::createVial()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
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

void MainWindow::createStaticVial()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
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

void MainWindow::createBeaker()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.position.Set(windowWidth  / 2 / SCALE, windowHeight / 6.75 / SCALE);
    staticVial = world->CreateBody(&bodyDef);

    staticVial->SetLinearDamping(3.0f);
    staticVial->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-2.0f, -2.75f); //bottom-left
    vertices[1].Set(-2.0f, 2.75f); //top-left
    vertices[2].Set(2.0f, 2.75f); //top-right
    vertices[3].Set(2.0f, -2.75f); //bottom-right

    createWall(staticVial, vertices[0], vertices[1]); // Left wall
    createWall(staticVial, vertices[2], vertices[3]); // Right wall
    createWall(staticVial, vertices[0], vertices[3]); // Bottom wall
}

void MainWindow::CreateStirRod()
{
    // Define a body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody; // Set the body to be dynamic
    bodyDef.position.Set(windowWidth  / 2 / SCALE, windowHeight / 10.25 / SCALE);
    b2Body *body = world->CreateBody(&bodyDef);

    // Assign a rectangular shape to the body
    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.05f, 1.75f);

    // Define fixture
    b2FixtureDef fixture;
    fixture.shape = &boxShape; // Assign shape to fixture
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.restitution = 0.3f;

    // Attach the fixture to the body
    body->CreateFixture(&fixture);

    body->SetAngularVelocity(2.0f);
}


void MainWindow::SpawnCircle(Chemical* chemical, b2Body* vial)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 vialPosition = vial->GetWorldCenter();
    bodyDef.position.Set(vialPosition.x, vialPosition.y);
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

void MainWindow::SpawnGas(b2Body* circle)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 circlePos = circle->GetWorldCenter();
    bodyDef.position.Set(circlePos.x, circlePos.y);
    b2Body* particle = world->CreateBody(&bodyDef);
    particle->SetGravityScale(-1);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.01f;
    fixtureDef.filter.categoryBits = 0;
    particle->CreateFixture(&fixtureDef);
}

void MainWindow::createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2)
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Q:
        vial->SetAngularVelocity(1);
        break;
    case Qt::Key_E:
        vial->SetAngularVelocity(-1);
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
    case Qt::Key_Z:
        b2Body* temp = vial;
        vial = staticVial;
        staticVial = temp;
    }


    update();
    // b2Vec2 vialPosition = vial->GetPosition();
    // float32 vialAngle = vial->GetAngle();
    // qDebug() << "Vial Position: (" << vialPosition.x << ", " << vialPosition.y << ")" << "Vial Angle: " << vialAngle;
}

void MainWindow::createScene()
{
    CreateStirRod();
    createBeaker();
    createVial();
    createStaticVial();

    createBorder();
    update();
    timer->start(1000 / 60);
}

void MainWindow::resetScene()
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

    for(int i = 0; i < 100; i++)
    {
        chemA[i] = Chemical(0, Qt::yellow, false);
    }

    for(int i = 0; i < 100; i++)
    {
        chemB[i] = Chemical(1, Qt::green, false);
    }

    world = new b2World(gravity);
    world->SetContactListener(&contact);
    chemCount = 0;
    createScene();
}

void MainWindow::drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge)
{
    QPen pen(Qt::black);
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    QPointF v1 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex1));
    QPointF v2 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex2));
    painter.drawLine(v1, v2);
}

void MainWindow::drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon)
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

void MainWindow::drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color)
{
    QPen pen(color);
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(color);
    QPointF position = convertCoordsBox2DToQt(body->GetPosition());
    painter.drawEllipse(position, circle->m_radius * SCALE, circle->m_radius * SCALE);
}

QPointF MainWindow::convertCoordsBox2DToQt(b2Vec2 vec)
{
    vec.x *= SCALE;
    vec.y = windowHeight - vec.y * SCALE;
    return QPointF(vec.x, vec.y);
}

void MainWindow::Update()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    vial->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    staticVial->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    world->Step(timeStep, velocityIterations, positionIterations);

    if(chemCount < 100) {
        SpawnCircle(&chemA[chemCount], vial);
        SpawnCircle(&chemB[chemCount], staticVial);
        chemCount++;

        // Apply a small force to the vials so the liquids don't stack
        vial->ApplyForceToCenter(b2Vec2(.01, 0), true);
        staticVial->ApplyForceToCenter(b2Vec2(-.01, 0), true);
    }

    b2Body* b = world->GetBodyList();

    while(b)
    {
        void* a = b->GetUserData();
        if(a)
        {
            Chemical* c = static_cast<Chemical*>(a);
            if(c->s_touch)
            {
                b2Body* d = b;
                b = b->GetNext();
                SpawnGas(d);
                world->DestroyBody(d);

            }
            else
            {
                b = b->GetNext();
            }
        }
        else
        {
            b = b->GetNext();
        }
    }

    update();
    vial->SetLinearVelocity(b2Vec2(0,0));
    staticVial->SetLinearVelocity(b2Vec2(0,0));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete world;
}

