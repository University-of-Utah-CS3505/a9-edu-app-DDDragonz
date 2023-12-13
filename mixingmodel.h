#ifndef MIXINGMODEL_H
#define MIXINGMODEL_H

#include "mixinglogic.h"
#include "mixingchemical.h"
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
    /// @param event The object that triggered the event.
    void mouseMoveEvent(QMouseEvent *event) override;

    /// @brief Moves the vial according to keyboard input only if the vial exists
    /// @param event the object that triggered the event.
    void keyPressEvent(QKeyEvent *event) override;

    /// @brief Moves the world objects to fit window
    /// @param event The object that triggered the event.
    void resizeEvent(QResizeEvent* event) override;

    /// @brief Paints an edge
    /// @param painter What to draw with
    /// @param body The object to get details from
    /// @param edge The edge to draw
    void drawEdge(QPainter& painter, b2Body* body, b2EdgeShape* edge);

    /// @brief Paints a polygon
    /// @param painter What to draw with
    /// @param body The object to get details from
    /// @param polygon The polygon to draw
    /// @param color The color to draw the polygon with
    /// @param notSolid A bool determining whether or not the polygon is a chemical solid
    void drawPolygon(QPainter& painter, b2Body* body, b2PolygonShape* polygon, QColor color, bool notSolid);

    /// @brief Paints a circle
    /// @param painter What to draw with
    /// @param body The object to get details from
    /// @param circle The circle to draw
    /// @param color The color to draw the circles
    void drawCircle(QPainter& painter, b2Body* body, b2CircleShape* circle, QColor color);

    /// @brief Displays a help menu on how to move the vials around
    void showControls();

signals:
    /// @brief A call to clear the scene
    void resetScene();

public slots:
    /// @brief Updates the state world based on a timer
    void updateWorld();

    /// @brief Removes all bodies from the world
    void eraseScene();

    /// @brief Creates all objects of the world and default sets the chemicals
    /// @param reaction The information to produce when chemicals are mixing
    void createScene(Reaction reaction);

private:
    QTimer *m_timer;
    Ui::MixingModel *m_ui;
    MixingLogic *m_world;
    float m_windowWidth;
    float m_scale = 20.0f;
    float m_windowHeight;
    Reaction m_reactionResult;
    QPushButton *m_helpButton;
    std::vector<MixingChemical> m_mixingChemicals;
    MixingChemical m_chemA[200];
    MixingChemical m_chemB[200];

    int m_chemCount = 0;

    /// @brief Converts Box2D coordinates to Qt.
    /// @param vect The x,y coordinates to scale
    /// @return the coordinates in Qt
    QPointF convertCoordsBox2DToQt(b2Vec2 vec);

    /// @brief Sets the paint color
    /// @param painter The painter object
    /// @param color The color to paint in
    /// @param brush The style of brush
    void setPaintColor(QPainter& painter, QColor color, QBrush brush);
};

#endif // MIXINGMODEL_H
