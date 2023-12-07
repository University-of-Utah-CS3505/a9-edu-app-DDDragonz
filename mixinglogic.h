#ifndef MIXINGLOGIC_H
#define MIXINGLOGIC_H

#include <QObject>
#include <Box2D/Box2D.h>
#include "contactlistener.h"
#include "chemicalBox2D.h"

class MixingLogic
{

public:
    /// @brief Constructor that creates the world
    /// @param width the world width
    /// @param height the world height
    /// @param scale the world scale
    MixingLogic(float width, float height, float scale);

    /// @brief Standard Deconstructor
    ~MixingLogic();

    /// @brief Creates a boundary for the world
    void createBorder();

    /// @brief Creates a dynamic body in the shape of a vial positioned on the left part of the screen
    void createVial();

    /// @brief Creates a dynamic body in the shape of a beaker positioned on the lower part of the screen
    void createBeaker();

    /// @brief Creates a spinning kinematic rectangle inside the beaker
    void createStirRod();

    /// @brief Creates a new world and sets the collision detector
    void createNewWorld();

    /// @brief Creates a rectangle with a thickness based on the given vertices.
    /// @param the body the object to create a fixture
    /// @param vertex1  position of the first point
    /// @param vertex2  position of the second point
    void createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2);

    /// @brief Creates a circle and assigns its user data
    /// @param chemical the chemical to assign to the circle
    /// @param vial the specific vial to spawn them in
    void spawnCircle(chemicalBox2D* chemical, b2Body* vial);

    /// @brief Creates a circle that has negative gravity at the point of collision with another body
    /// @param circle the circle instance in the world
    void spawnGas(b2Body* circle);

    /// @brief Creates a square that acts as a solid formed from chemicals.
    /// @param circle the circle instance in the world
    void spawnSolid(b2Body* circle);

    /// @brief Set the width of the window
    /// @param newWidth the new width
    void setWindowWidth(int newWidth);

    /// @brief Set the height of the window
    /// @param newHeight the new height
    void setWindowHeight(int newHeight);

    /// @brief Set the scale of the window
    /// @param newScale the new scale
    void setWorldScale(float newScale);

    /// @brief Returns the user vial
    b2Body* getVial() const;

    /// @brief Returns the beaker
    b2Body* getBeaker() const;

    /// @brief Sets the vial
    /// @param otherVial the new vial
    void setVial(b2Body* otherVial);

    /// @brief Sets the static vial
    /// @param otherVial the new vial
    void setBeaker(b2Body* otherVial);

    /// @brief Returns the world
    b2World* getWorld() const;

    /// @brief Return true if the vial was draw, false otherwise
    bool getIsVialDrawn();

    /// @brief Set the state of if the vial is currently drawn
    /// @param state true if drawn, false otherwise
    void setIsVialDrawn(bool state);

private:
    b2Body* m_vial;
    b2Body* m_beaker;
    bool m_isVialDrawn;
    float m_worldScale;
    float m_windowWidth;
    float m_windowHeight;
    b2World *m_logicWorld;
    myContactListener m_contact;

    /// @brief Sets the fixture of a body
    /// @param body the object to which the fixture is applied
    /// @param shape the shape of the body
    /// @param density the mass of the body
    /// @param friction determines resistance to sliding against other bodies
    /// @param restitution determines the elasticity of collisions
    void createFixutre(b2Body* body, b2Shape* shape, float density, float friction, float restitution);
};

#endif // MIXINGLOGIC_H
