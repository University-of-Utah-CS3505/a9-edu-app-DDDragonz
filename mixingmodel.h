#ifndef MIXINGMODEL_H
#define MIXINGMODEL_H

#include "mixinglogic.h"
#include <QWidget>
#include <Box2D/Box2D.h>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class MixingModel;
}

class MixingModel : public QWidget
{
    Q_OBJECT

public:
    MixingModel(QWidget *parent = nullptr);
    ~MixingModel();

    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void createScene();
    void eraseScene();

    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon);
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color);

    /// @brief Converts Box2D coordinates to Qt.
    /// @param vect The x,y coordinates to scale
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);

public slots:
    void updateWorld();

private:
    Ui::MixingModel *ui;
    QTimer *timer;
    const float SCALE = 32.0f;
    float windowWidth;
    float windowHeight;
    MixingLogic *worldPtr;

//    std::vector<Chemical> chemicals;
//    Chemical chemA[100];
//    Chemical chemB[100];

    void setPaintColor(QPainter& painter, QColor color, QBrush brush);

};

#endif // MIXINGMODEL_H
