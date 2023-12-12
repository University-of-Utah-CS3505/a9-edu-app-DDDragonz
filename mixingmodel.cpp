#include "mixingmodel.h"
#include "ui_mixingmodel.h"
#include "mixingchemical.h"
#include <QPixmap>
#include <QImage>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

MixingModel::MixingModel(QWidget *parent) :
    QWidget(parent),
    m_timer(new QTimer(this)),
    m_ui(new Ui::MixingModel),
    m_reactionResult(*new vector<Chemical>),
    m_chemA(),
    m_chemB()
{
    m_ui->setupUi(this);
    m_windowWidth = this->width();
    m_windowHeight = this->height() - this->height();
    m_world = new MixingLogic(m_windowWidth, m_windowHeight, m_scale);
    connect(m_timer,
            &QTimer::timeout,
            this,
            &MixingModel::updateWorld);
    connect(m_ui->helpButton, &QPushButton::clicked, this, &MixingModel::showControls);
}

MixingModel::~MixingModel()
{
    delete m_ui;
    delete m_timer;
    delete m_world;
}

void MixingModel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QImage bgImage(":/images/gray.jpg");
    painter.drawImage(this->rect(), bgImage);
    
    for (b2Body* body = m_world->getWorld()->GetBodyList(); body != 0; body = body->GetNext())
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
                    MixingChemical c = *static_cast<MixingChemical*>(body->GetUserData());
                    drawCircle(painter, body, (b2CircleShape*)shape, c.s_color);
                }
                else
                {
                    drawCircle(painter, body, (b2CircleShape*)shape, Qt::white);
                }
            }
            else if (shape->GetType() == b2Shape::e_polygon)
            {
                if(body->GetFixtureList()->GetDensity() == 6.0f)
                {
                    drawPolygon(painter, body, (b2PolygonShape*)shape, m_reactionResult.colorOfSolid(), false);
                }
                else
                {
                    drawPolygon(painter, body, (b2PolygonShape*)shape, Qt::black, true);
                }
            }
        }
    }
}

void MixingModel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && m_world->getIsVialDrawn())
    {
        b2Vec2 pos(event->pos().x() / m_scale, (m_windowHeight - event->pos().y()) / m_scale);
        b2Vec2 velocity = pos - m_world->getVial()->GetPosition();
        float velocitym_scale = 3.0f;
        velocity *= velocitym_scale;
        m_world->getVial()->SetLinearVelocity(velocity);
        update();
    }
}

void MixingModel::keyPressEvent(QKeyEvent *event)
{
    if(m_world->getIsVialDrawn())
    {
        switch(event->key())
        {
        case Qt::Key_Q:
            m_world->getVial()->SetAngularVelocity(1);
            break;
        case Qt::Key_E:
            m_world->getVial()->SetAngularVelocity(-1);
            break;
        case Qt::Key_W:
            m_world->getVial()->ApplyLinearImpulse(b2Vec2(0.0f, 10.0f), m_world->getVial()->GetWorldCenter(), true);
            break;
        case Qt::Key_A:
            m_world->getVial()->ApplyLinearImpulse(b2Vec2(-10.0f, 0.0f), m_world->getVial()->GetWorldCenter(), true);
            break;
        case Qt::Key_S:
            m_world->getVial()->ApplyLinearImpulse(b2Vec2(0.0f, -10.0f), m_world->getVial()->GetWorldCenter(), true);
            break;
        case Qt::Key_D:
            m_world->getVial()->ApplyLinearImpulse(b2Vec2(10.0f, 0.0f), m_world->getVial()->GetWorldCenter(), true);
            break;
        }
        update();
    }
}

void MixingModel::resizeEvent(QResizeEvent *event)
{
    QSize newSize = event->size();
    float newScale = newSize.width() / m_windowWidth;
    m_scale *= newScale;
    m_windowWidth = newSize.width();
    m_windowHeight = newSize.height();
    m_world->setWindowWidth(m_windowWidth);
    m_world->setWindowHeight(m_windowHeight);
    m_world->setWorldScale(m_scale);
    emit resetScene();
    eraseScene();
}

void MixingModel::drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge)
{
    setPaintColor(painter, Qt::black, Qt::NoBrush);
    QPointF v1 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex1));
    QPointF v2 = convertCoordsBox2DToQt(body->GetWorldPoint(edge->m_vertex2));
    painter.drawLine(v1, v2);
}

void MixingModel::drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon, QColor color, bool notSolid)
{
    if(notSolid)
    {
        setPaintColor(painter, Qt::black, Qt::NoBrush);
    }
    else
    {
        setPaintColor(painter, color, color);
    }

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
    painter.drawEllipse(position, circle->m_radius * m_scale, circle->m_radius * m_scale);
}

void MixingModel::showControls()
{
    QDialog *dialog = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel("W-Move Up\nS-Move Down\n"
                               "A-Move Left\nD-Move Right\n"
                               "Q-Tilt Left\nE-Tilt Right\n"
                               "Trackpad-Drag vial\n"
                               "Resizing the window resets your mixing space\n"
                               "Giving an incorrect response also resets your mixing space");
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
    m_world->getVial()->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    m_world->getBeaker()->ApplyForceToCenter(b2Vec2(0.0f, 14.0f), true);
    m_world->getWorld()->Step(timeStep, velocityIterations, positionIterations);

    if(m_chemCount < 100)
    {
        m_world->spawnCircle(&m_chemA[m_chemCount], m_world->getVial());
        m_world->spawnCircle(&m_chemB[m_chemCount], m_world->getBeaker());
        m_chemCount++;

        // Apply a small force to the vials so the liquids don't stack
        m_world->getVial()->ApplyForceToCenter(b2Vec2(.01, 0), true);
        m_world->getBeaker()->ApplyForceToCenter(b2Vec2(-.01, 0), true);
    }
    b2Body* b = m_world->getWorld()->GetBodyList();
    while(b)
    {
        void* a = b->GetUserData();
        if(a)
        {
            MixingChemical* c = static_cast<MixingChemical*>(a);
            if(c->s_touch)
            {
                bool destroy = false;
                b2Body* d = b;
                b = b->GetNext();
                if(m_reactionResult.hasGas())
                {
                    m_world->spawnGas(d);
                    destroy = true;
                }
                if(m_reactionResult.hasSolid())
                {
                    m_world->spawnSolid(d);
                    destroy = true;
                }
                if(destroy)
                {
                    m_world->getWorld()->DestroyBody(d);
                }
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
    m_world->getVial()->SetLinearVelocity(b2Vec2(0,0));
    m_world->getBeaker()->SetLinearVelocity(b2Vec2(0,0));
}

void MixingModel::eraseScene()
{
    m_timer->stop();

    std::vector<b2Body*> bodiesToDestroy;
    
    for (b2Body* body = m_world->getWorld()->GetBodyList(); body != 0; body = body->GetNext())
    {
        bodiesToDestroy.push_back(body);
    }

    for (b2Body* body : bodiesToDestroy)
    {
        m_world->getWorld()->DestroyBody(body);
    }
    
    m_world->getWorld()->Step(1/60.f, 6, 2); // make sure everything is deleted
    m_world->createNewWorld();
    for(int i = 0; i < 100; i++)
    {
        m_chemA[i] = MixingChemical(0, Qt::blue, false);
        m_chemB[i] = MixingChemical(1, Qt::blue, false);
    }

    m_chemCount = 0;
    update();
    m_world->setIsVialDrawn(false);
}

void MixingModel::createScene(Reaction reaction)
{
    m_reactionResult = reaction;
    m_world->createBorder();
    m_world->createVial();
    m_world->createBeaker();
    m_world->createStirRod();


    for(int i = 0; i < 100; i++)
    {
        m_chemA[i] = MixingChemical(0, Qt::blue, false);
        m_chemB[i] = MixingChemical(1, Qt::blue, false);
    }

    update();
    m_world->setIsVialDrawn(true);
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
    vec.x *= m_scale;
    vec.y = m_windowHeight - vec.y * m_scale;
    return QPointF(vec.x, vec.y);
}
