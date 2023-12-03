#ifndef MW_H
#define MW_H

#include "contactlistener.h"

#include <vector>

#include <QMainWindow>
#include <Box2D/Box2D.h>
#include <QTimer>

#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MW; }
QT_END_NAMESPACE

struct Chemical{
    int s_id;
    QColor s_color;

    Chemical(int id, QColor color) : s_id(id), s_color(color) {};
    Chemical() {s_id = 0; s_color = Qt::green;}
};

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();

    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void createVial();
    void createStaticVial();
    void createVialLiquid(int numParticles);
    void createBorder();
    void createGround();
    void createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2);
    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color);
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon);
    void resetScene();
    void SpawnCircle(Chemical* chemical, b2Body* vial, float32 offset);
    void createScene();



    void SpawnBox();

public slots:
    void Update();

private:
    Ui::MW *ui;
    b2World *world;
    QTimer *timer;
    b2Body* vial;
    b2Body* staticVial;

    myContactListener contact;

    const float SCALE = 32.0f;
    float windowWidth;
    float windowHeight;

    Chemical *chemA;
    Chemical *chemB;

    /// Box2D to Qt (meters to pixels), you multiply by SCALE.
    /// Qt to Box2D (pixels to meters), you divide by SCALE.
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);
};
#endif // MW_H
