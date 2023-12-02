#ifndef MIXINGLOGIC_H
#define MIXINGLOGIC_H

#include <QObject>
#include <Box2D/Box2D.h>
#include "contactlistener.h"

//struct Chemical{
//    int s_id;
//    QColor s_color;

//    Chemical(int id, QColor color) : s_id(id), s_color(color) {};
//    Chemical() {s_id = 0; s_color = Qt::green;}
//};

class MixingLogic
{

public:
    MixingLogic(float width, float height, float scale);
    ~MixingLogic();

    void createBorder();
    void createVial();
    void createStaticVial();

    //void SpawnCircle(Chemical* chemical, b2Body* vial);
    void spawnCircle(b2Body* vial);

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

    //    std::vector<Chemical> chemicals;
    //    Chemical chemA[100];
    //    Chemical chemB[100];

    int chh = 0;
    void createFixutre(b2Body* body, b2Shape* shape, float32 density, float32 friction, float restitution);
};

#endif // MIXINGLOGIC_H
