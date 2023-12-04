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
#include "chemical.h"

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

    void eraseScene();

    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon);
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color);

    /// @brief Converts Box2D coordinates to Qt.
    /// @param vect The x,y coordinates to scale
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);

public slots:
    void updateWorld();
    //void createScene(Chemical* chemical1, Chemical* chemical2, QVector<Reaction> reactions);
    void createScene();

private:
    Ui::MixingModel *ui;
    QTimer *timer;
    const float SCALE = 32.0f;
    float windowWidth;
    float windowHeight;
    MixingLogic *world;

    //Chemical* chemical1;
    //Chemical* chemical2;

    std::vector<Chemical> chemicals;
    Chemical chemA[200];
    Chemical chemB[200];

    int chemCount = 0;

    void setPaintColor(QPainter& painter, QColor color, QBrush brush);

};

#endif // MIXINGMODEL_H
