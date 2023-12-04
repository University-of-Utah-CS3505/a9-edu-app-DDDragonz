#ifndef MIXINGLOGIC_H
#define MIXINGLOGIC_H

#include <QObject>
#include <Box2D/Box2D.h>
#include "contactlistener.h"
#include "chemicalBox2D.h"

class MixingLogic
{

public:
    MixingLogic(float width, float height, float scale);
    ~MixingLogic();

    void createBorder();
    void createVial();
    void createBeaker();
    void createStirRod();
    void createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2);
    void createWalls(int numberOfVerts, float32 xPos, float32 yPos, b2Body* body);
    void createNewWorld();

    //void spawnCircle(b2Body* vial);
    void spawnCircle(chemicalBox2D* chemical, b2Body* vial);
    void spawnGas(b2Body* circle);

    b2Body* getVial() const;
    b2Body* getStaticVial() const;
    void setVial(b2Body* otherVial);
    void setStaticVial(b2Body* otherVial);
    b2World* getWorld() const;

private:
    b2World *logicWorld;
    b2Body* vial;
    b2Body* staticVial;

    myContactListener contact;

    const float SCALE;
    float windowWidth;
    float windowHeight;

    void createFixutre(b2Body* body, b2Shape* shape, float32 density, float32 friction, float restitution);
};

#endif // MIXINGLOGIC_H
