#include "mixingmodel.h"
#include "ui_mixingmodel.h"

MixingModel::MixingModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MixingModel),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    windowWidth = this->width();
    windowHeight = this->height() - 50;
    worldPtr = new MixingLogic(windowWidth, windowHeight, SCALE);

    connect(timer,
            &QTimer::timeout,
            this,
            &MixingModel::updateWorld);

    connect(ui->reset,
            &QPushButton::clicked,
            this,
            &MixingModel::eraseScene);

    //after pressing mix recieve everything all at once and connect to createScene
   //mixinglogic deals with creating the liquid
//    for(int i = 0; i < 100; i++)
//    {
//        chemA[i] = Chemical(0, Qt::yellow);
//    }

//    for(int i = 0; i < 100; i++)
//    {
//        chemB[i] = Chemical(1, Qt::green);
//    }
    createScene();
}

MixingModel::~MixingModel()
{
    delete ui;
    delete timer;
    delete worldPtr;
}

void MixingModel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for (b2Body* body = worldPtr->getWorld()->GetBodyList(); body != 0; body = body->GetNext())
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
                //Chemical c = *static_cast<Chemical*>(body->GetUserData());
                drawCircle(painter, body, (b2CircleShape*)shape, Qt::black);
            }
            else if (shape->GetType() == b2Shape::e_polygon)
            {
                drawPolygon(painter, body, (b2PolygonShape*)shape);
            }
        }
    }
}

void MixingModel::mouseMoveEvent(QMouseEvent *event)
{
    b2Vec2 pos(event->pos().x() / SCALE, (windowHeight - event->pos().y()) / SCALE);
    b2Vec2 velocity = pos - worldPtr->getVial()->GetPosition();
    float velocityScale = 3.0f; //Changeable
    velocity *= velocityScale;
    worldPtr->getVial()->SetLinearVelocity(velocity);
    update();
}

void MixingModel::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Q:
        worldPtr->getVial()->SetAngularVelocity(-1);
        break;
    case Qt::Key_E:
        worldPtr->getVial()->SetAngularVelocity(1);
        break;
    case Qt::Key_W:
        worldPtr->getVial()->ApplyLinearImpulse(b2Vec2(0.0f, 10.0f), worldPtr->getVial()->GetWorldCenter(), true);
        break;
    case Qt::Key_A:
        worldPtr->getVial()->ApplyLinearImpulse(b2Vec2(-10.0f, 0.0f), worldPtr->getVial()->GetWorldCenter(), true);
        break;
    case Qt::Key_S:
        worldPtr->getVial()->ApplyLinearImpulse(b2Vec2(0.0f, -10.0f), worldPtr->getVial()->GetWorldCenter(), true);
        break;
    case Qt::Key_D:
        worldPtr->getVial()->ApplyLinearImpulse(b2Vec2(10.0f, 0.0f), worldPtr->getVial()->GetWorldCenter(), true);
        break;
    }
    update();
}

void MixingModel::createScene()
{
    worldPtr->createBorder();
    worldPtr->createVial();
    worldPtr->createStaticVial();

    for (int i = 0; i < 99; i++)
    {
        worldPtr->spawnCircle(worldPtr->getVial());
    }

    for (int i = 0; i < 99; i++)
    {
        worldPtr->spawnCircle(worldPtr->getStaticVial());
    }

    //    Chemical c(0, Qt::red);
    //    for (int i = 0; i < 99; i++)
    //    {
    //        SpawnCircle(&chemA[i], worldPtr->getVial());
    //    }

    //    for (int i = 0; i < 99; i++)
    //    {
    //        SpawnCircle(&chemB[i], orldPtr->getStaticVial());
    //    }


    //    SpawnCircle(&chemicals[0]);
    //    SpawnCircle(&chemicals[1]);
    update();
    timer->start(1000 / 60);
}

void MixingModel::eraseScene()
{
    timer->stop();
    for (b2Body* body = worldPtr->getWorld()->GetBodyList(); body != 0; body = body->GetNext())
    {
        worldPtr->getWorld()->DestroyBody(body);
    }
    worldPtr->getWorld()->Step(1/60.f, 8, 3); // make sure everything is deleted
    worldPtr->createNewWorld();
    //    chh = 0;
    createScene();
}

void MixingModel::updateWorld()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    worldPtr->getVial()->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    worldPtr->getWorld()->Step(timeStep, velocityIterations, positionIterations);
    //    if(chh < 100) {
    //        SpawnCircle(&chemA[chh], vial);
    //        SpawnCircle(&chemB[chh], staticVial);
    //        chh++;
    //    }
    update();
    worldPtr->getVial()->SetLinearVelocity(b2Vec2(0,0));
}

void MixingModel::drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge)
{
    setPaintColor(painter, Qt::black, Qt::NoBrush);
    QPointF v1 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex1));
    QPointF v2 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex2));
    painter.drawLine(v1, v2);
}

void MixingModel::drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon)
{
    setPaintColor(painter, Qt::black, Qt::NoBrush);
    QPolygonF qpolygon;
    for (int32 i = 0; i < polygon->m_count; ++i)
    {
        QPointF v = convertCoordsBox2DToQt(body->GetWorldPoint(polygon->m_vertices[i]));
        qpolygon.append(v);
    }
    painter.drawPolygon(qpolygon);
}

void MixingModel::drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color)
{
    setPaintColor(painter, color, color);
    QPointF position = convertCoordsBox2DToQt(body->GetPosition());
    painter.drawEllipse(position, circle->m_radius * SCALE, circle->m_radius * SCALE);
}

void MixingModel:: setPaintColor(QPainter& painter, QColor color, QBrush brush)
{
    QPen pen(color);
    pen.setWidth(0);
    painter.setPen(pen);
    painter.setBrush(brush);
}

QPointF MixingModel::convertCoordsBox2DToQt(b2Vec2 vec)
{
    vec.x *= SCALE;
    vec.y = windowHeight - vec.y * SCALE;
    return QPointF(vec.x, vec.y);
}
