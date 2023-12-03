#ifndef MIXINGLOGIC_H
#define MIXINGLOGIC_H

#include <QObject>
#include <Box2D/Box2D.h>
#include "contactlistener.h"

class MixingLogic
{

public:
    MixingLogic(float width, float height, float scale);
    ~MixingLogic();

    void createBorder();
    void createVial();
    void createStaticVial();

    void spawnCircle(b2Body* vial);
    //void spawnCircle(Chemical* chemical, b2Body* vial);

    void createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2);
    void createNewWorld();

    b2Body* getVial() const;
    b2Body* getStaticVial() const;
    b2World* getWorld() const;

private:
    b2World *world;
    b2Body* vial;
    b2Body* staticVial;

    myContactListener contact;

    const float SCALE;
    float windowWidth;
    float windowHeight;

    void createFixutre(b2Body* body, b2Shape* shape, float32 density, float32 friction, float restitution);
};

#endif // MIXINGLOGIC_H
