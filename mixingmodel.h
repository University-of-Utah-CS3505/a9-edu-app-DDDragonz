#ifndef MIXINGMODEL_H
#define MIXINGMODEL_H

#include "mixinglogic.h"
#include "chemicalBox2D.h"
#include "reaction.h"
#include <QWidget>
#include <Box2D/Box2D.h>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>

namespace Ui {
class MixingModel;
}

class MixingModel : public QWidget
{
    Q_OBJECT

public:
    /// @brief Standard Constructor. Sets the width, height, makes an instance of MixingLogic, and makes connections
    MixingModel(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor
    ~MixingModel();

    /// @brief Paints all Box2D instances and background
    void paintEvent(QPaintEvent*) override;

    /// @brief Moves the vial around only if it exists
    /// @param event the object that triggered the event.
    void mouseMoveEvent(QMouseEvent *event) override;

    /// @brief Moves the vial according to keyboard input only if the vial exists
    /// @param event the object that triggered the event.
    void keyPressEvent(QKeyEvent *event) override;


    //FIX!!
    /// @brief Resizes stuff
    /// @param event the object that triggered the event.
    void resizeEvent(QResizeEvent* event) override;

    /// @brief Paints an edge
    /// @param painter what to draw with
    /// @param body the object to get details from
    /// @param edge the edge to draw
    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);

    /// @brief Paints a polygon
    /// @param painter what to draw with
    /// @param body the object to get details from
    /// @param polygon the polygon to draw
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon);

    /// @brief Paints a circle
    /// @param painter what to draw with
    /// @param body the object to get details from
    /// @param circle the circle to draw
    /// @param color the color to draw the circles
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color);

    /// @brief Displays a help menu on how to move the vials around
    void showControls();

public slots:
    /// @brief Updates the state world based on a timer
    void updateWorld();

    /// @brief Removes all bodies from the world
    void eraseScene();

    void createScene();

    /// @brief
    /// @param cheimcal1
    /// @param chemical2
    /// @param reactionResult
    void createScene2(Chemical chemical1, Chemical chemical2, Reaction reactionResult);

private:
    QTimer *m_timer;
    Ui::MixingModel *ui;
    MixingLogic *world;
    float m_windowWidth;
    float SCALE = 20.0f;
    float m_windowHeight;
    QPushButton *m_helpButton;

    std::vector<chemicalBox2D> chemicalBox2Ds;
    chemicalBox2D chemA[200];
    chemicalBox2D chemB[200];

    int chemCount = 0;

    /// @brief Converts Box2D coordinates to Qt.
    /// @param vect The x,y coordinates to scale
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);

    /// @brief Sets the paint color
    /// @param painter the painter object
    /// @param color the color to paint in
    /// @param brush the style of brush
    void setPaintColor(QPainter& painter, QColor color, QBrush brush);
};

#endif // MIXINGMODEL_H
