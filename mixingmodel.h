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
#include "chemicalBox2D.h"
#include "reaction.h"

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

    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon);
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color);

    /// @brief Converts Box2D coordinates to Qt.
    /// @param vect The x,y coordinates to scale
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);

    MixingLogic *world;

public slots:
    void updateWorld();
    void eraseScene();
    void createScene();
    void createScene2(QString chemical1, QString chemical2, Reaction reactionResult);

private:
    Ui::MixingModel *ui;
    QTimer *timer;
    const float SCALE = 20.0f;
    float windowWidth;
    float windowHeight;


    //chemicalBox2D* chemicalBox2D1;
    //chemicalBox2D* chemicalBox2D2;

    std::vector<chemicalBox2D> chemicalBox2Ds;
    chemicalBox2D chemA[200];
    chemicalBox2D chemB[200];

    int chemCount = 0;

    int count = 0;

    void setPaintColor(QPainter& painter, QColor color, QBrush brush);

};

#endif // MIXINGMODEL_H
