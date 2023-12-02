#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "contactlistener.h"
#include <QMainWindow>
#include <Box2D/Box2D.h>
#include <QTimer>

#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void createVial();
    void createVialLiquid(int numParticles);
    void createBorder();
    void createGround();
    void createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2);
    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle);
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon);
    void resetScene();
    void SpawnCircle();
    void createScene();



    void SpawnBox();

public slots:
    void Update();

private:
    Ui::MainWindow *ui;
    b2World *world;
    QTimer *timer;
    b2Body* vial;

    myContactListener contact;

    const float SCALE = 32.0f;
    float windowWidth;
    float windowHeight;

    /// Box2D to Qt (meters to pixels), you multiply by SCALE.
    /// Qt to Box2D (pixels to meters), you divide by SCALE.
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);
};
#endif // MAINWINDOW_H
