#ifndef MIXINGLOGIC_H
#define MIXINGLOGIC_H

#include <QObject>
#include <Box2D/Box2D.h>
#include "contactlistener.h"
#include "mixingchemical.h"

class MixingLogic
{

public:
    /// @brief Constructor that creates the world
    /// @param width The world width
    /// @param height The world height
    /// @param scale The world scale
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
    /// @param body The object to create a fixture on
    /// @param vertex1  Position of the first point
    /// @param vertex2  Position of the second point
    void createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2);

    /// @brief Creates a circle and assigns its user data
    /// @param chemical The chemical to assign to the circle
    /// @param vial The vial to spawn them in
    void spawnCircle(MixingChemical* chemical, b2Body* vial);

    /// @brief Creates a circle that has negative gravity at the point of collision with another body
    /// @param circle The circle instance in the world
    void spawnGas(b2Body* circle);

    /// @brief Creates a square that acts as a solid formed from chemicals.
    /// @param circle The circle instance in the world
    void spawnSolid(b2Body* circle);

    /// @brief Set the width of the window
    /// @param newWidth The new width
    void setWindowWidth(int newWidth);

    /// @brief Set the height of the window
    /// @param newHeight The new height
    void setWindowHeight(int newHeight);

    /// @brief Set the scale of the window
    /// @param newScale The new scale
    void setWorldScale(float newScale);

    /// @brief The vial and all of its attributes
    /// @return the vial
    b2Body* getVial() const;

    /// @brief The beaker and all of its attributes
    /// @return the beaker
    b2Body* getBeaker() const;

    /// @brief Sets the vial
    /// @param otherVial The new vial
    void setVial(b2Body* otherVial);

    /// @brief Sets the static vial
    /// @param otherVial The new beaker
    void setBeaker(b2Body* otherBeaker);

    /// @brief The world everything is contained in
    /// @return the world
    b2World* getWorld() const;

    /// @brief Return true if the vial was draw, false otherwise
    bool getIsVialDrawn();

    /// @brief Set the state of if the vial is currently drawn
    /// @param state True if drawn, false otherwise
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
    /// @param body The object to which the fixture is applied
    /// @param shape The shape of the body
    /// @param density The mass of the body
    /// @param friction Determines resistance to sliding against other bodies
    /// @param restitution Determines the elasticity of collisions
    /// @param collisions Should they detect collisions
    void createFixutre(b2Body* body, b2Shape* shape, float density, float friction, float restitution, bool collisions);
};

#endif // MIXINGLOGIC_H
