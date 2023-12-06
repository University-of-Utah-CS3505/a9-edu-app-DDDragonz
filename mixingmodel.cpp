#include "mixingmodel.h"
#include "ui_mixingmodel.h"
#include "chemicalBox2D.h"
#include <QPixmap>
#include <QImage>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

MixingModel::MixingModel(QWidget *parent) :
    QWidget(parent),
    m_timer(new QTimer(this)),
    ui(new Ui::MixingModel),
    chemA(),
    chemB()
{
    ui->setupUi(this);
    m_windowWidth = this->width();
    m_windowHeight = this->height() - 25;
    world = new MixingLogic(m_windowWidth, m_windowHeight, SCALE);
    connect(m_timer,
            &QTimer::timeout,
            this,
            &MixingModel::updateWorld);
    connect(ui->helpButton, &QPushButton::clicked, this, &MixingModel::showControls);
}

MixingModel::~MixingModel()
{
    delete ui;
    delete m_timer;
    delete world;
}

void MixingModel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QImage bgImage(":/images/image.jpg");
    painter.drawImage(this->rect(), bgImage);

    for (b2Body* body = world->getWorld()->GetBodyList(); body != 0; body = body->GetNext())
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
                    chemicalBox2D c = *static_cast<chemicalBox2D*>(body->GetUserData());
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

void MixingModel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && world->getIsVialDrawn())
    {
        b2Vec2 pos(event->pos().x() / SCALE, (m_windowHeight - event->pos().y()) / SCALE);
        b2Vec2 velocity = pos - world->getVial()->GetPosition();
        float velocityScale = 3.0f;
        velocity *= velocityScale;
        world->getVial()->SetLinearVelocity(velocity);
        update();
    }
}

void MixingModel::keyPressEvent(QKeyEvent *event)
{
    if(world->getIsVialDrawn())
    {
        switch(event->key())
        {
        case Qt::Key_Q:
            world->getVial()->SetAngularVelocity(1);
            break;
        case Qt::Key_E:
            world->getVial()->SetAngularVelocity(-1);
            break;
        case Qt::Key_W:
            world->getVial()->ApplyLinearImpulse(b2Vec2(0.0f, 10.0f), world->getVial()->GetWorldCenter(), true);
            break;
        case Qt::Key_A:
            world->getVial()->ApplyLinearImpulse(b2Vec2(-10.0f, 0.0f), world->getVial()->GetWorldCenter(), true);
            break;
        case Qt::Key_S:
            world->getVial()->ApplyLinearImpulse(b2Vec2(0.0f, -10.0f), world->getVial()->GetWorldCenter(), true);
            break;
        case Qt::Key_D:
            world->getVial()->ApplyLinearImpulse(b2Vec2(10.0f, 0.0f), world->getVial()->GetWorldCenter(), true);
            break;
        }
        update();
    }
}

void MixingModel::resizeEvent(QResizeEvent *event)
{
    QSize newSize = event->size();
    float newScale = newSize.width() / m_windowWidth;
    SCALE *= newScale;
    m_windowWidth = newSize.width();
    m_windowHeight = newSize.height() - 25;

    world->setWindowWidth(m_windowWidth);
    world->setWindowHeight(m_windowHeight);
    world->setWorldScale(SCALE);
    update();
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

void MixingModel::showControls()
{
    QDialog *dialog = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel("W-Move Up\nS-Move Down\n"
                               "A-Move Left\nD-Move Right\n"
                               "Q-Tilt Left\nE-Tilt Right\n"
                               "Trackpad-Drag vial");

    layout->addWidget(label);
    dialog->setLayout(layout);
    dialog->setWindowTitle("Mixing Help");
    dialog->exec();
}

void MixingModel::updateWorld()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world->getVial()->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    world->getBeaker()->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    world->getWorld()->Step(timeStep, velocityIterations, positionIterations);

    if(chemCount < 100)
    {
        world->spawnCircle(&chemA[chemCount], world->getVial());
        world->spawnCircle(&chemB[chemCount], world->getBeaker());
        chemCount++;

        // Apply a small force to the vials so the liquids don't stack
        world->getVial()->ApplyForceToCenter(b2Vec2(.01, 0), true);
        world->getBeaker()->ApplyForceToCenter(b2Vec2(-.01, 0), true);
    }
    b2Body* b = world->getWorld()->GetBodyList();
    while(b)
    {
        void* a = b->GetUserData();
        if(a)
        {
            chemicalBox2D* c = static_cast<chemicalBox2D*>(a);
            if(c->s_touch)
            {
                b2Body* d = b;
                b = b->GetNext();
                world->spawnGas(d);
                world->getWorld()->DestroyBody(d);
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
    world->getVial()->SetLinearVelocity(b2Vec2(0,0));
    world->getBeaker()->SetLinearVelocity(b2Vec2(0,0));
}

void MixingModel::eraseScene()
{
    m_timer->stop();

    std::vector<b2Body*> bodiesToDestroy;

    for (b2Body* body = world->getWorld()->GetBodyList(); body != 0; body = body->GetNext())
    {
        bodiesToDestroy.push_back(body);
    }

    for (b2Body* body : bodiesToDestroy)
    {
        world->getWorld()->DestroyBody(body);
    }

    world->getWorld()->Step(1/60.f, 6, 2); // make sure everything is deleted
    world->createNewWorld();
    for(int i = 0; i < 100; i++)
    {
        chemA[i] = chemicalBox2D(0, Qt::blue, false);
    }

    for(int i = 0; i < 100; i++)
    {
        chemB[i] = chemicalBox2D(1, Qt::blue, false);
    }
    chemCount = 0;
    update();
    world->setIsVialDrawn(false);
}

void MixingModel::createScene2(Chemical chemical1, Chemical chemical2, Reaction reactionResult)
{
    Reaction r = reactionResult;
    qDebug() << "Recieved " << chemical1.getFormula() << " and " << chemical2.getFormula();
    qDebug() << "Color " << r.colorOfSolid() << " Gas? " << r.hasGas() << "Solid? " << r.hasSolid() << "mixing model";
}

void MixingModel::createScene()
{
    world->createBorder();
    world->createVial();
    world->createBeaker();
    world->createStirRod();
    for(int i = 0; i < 100; i++)
    {
        chemA[i] = chemicalBox2D(0, Qt::blue, false);
    }

    for(int i = 0; i < 100; i++)
    {
        chemB[i] = chemicalBox2D(1, Qt::blue, false);
    }
    update();
    world->setIsVialDrawn(true);
    m_timer->start(1000 / 60);
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
    vec.y = m_windowHeight - vec.y * SCALE;
    return QPointF(vec.x, vec.y);
}
