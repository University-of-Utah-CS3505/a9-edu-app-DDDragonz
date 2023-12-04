#include "mixinglogic.h"
#include "contactlistener.h"
#include "chemicalBox2D.h"

MixingLogic::MixingLogic(float width, float height, const float scale) :
    world(new b2World(b2Vec2(0.0f, -10.0f))),
    SCALE(scale),
    windowWidth(width),
    windowHeight(height)
{
    world->SetContactListener(&contact);
}

void MixingLogic::createBorder()
{
    //Define body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(0, 0);
    b2Body* body = world->CreateBody(&bodyDef);
    b2EdgeShape edge;

    // Bottom border
    edge.Set(b2Vec2(0, 0), b2Vec2(windowWidth / SCALE, 0));
    body->CreateFixture(&edge, 0);

    // Left border
    edge.Set(b2Vec2(0, 0), b2Vec2(0, windowHeight / SCALE));
    body->CreateFixture(&edge, 0);

    // Top border
    edge.Set(b2Vec2(0, windowHeight / SCALE), b2Vec2(windowWidth / SCALE, windowHeight / SCALE));
    body->CreateFixture(&edge, 0);

    // Right border
    edge.Set(b2Vec2(windowWidth / SCALE, 0), b2Vec2(windowWidth / SCALE, windowHeight / SCALE));
    body->CreateFixture(&edge, 0);
}

void MixingLogic::createVial()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.position.Set(windowWidth  / 4 / SCALE, windowHeight / 3 / SCALE);
    vial = world->CreateBody(&bodyDef);

    vial->SetLinearDamping(3.0f);
    vial->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-1.0f, -3.0f); //bottom-left
    vertices[1].Set(-1.0f, 3.0f); //top-left
    vertices[2].Set(1.0f, 3.0f); //top-right
    vertices[3].Set(1.0f, -3.0f); //bottom-right

    createWall(vial, vertices[0], vertices[1]); // Left wall
    createWall(vial, vertices[2], vertices[3]); // Right wall
    createWall(vial, vertices[0], vertices[3]); // Bottom wall
}

void MixingLogic::createBeaker()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.position.Set(windowWidth  / 2 / SCALE, windowHeight / 6.75 / SCALE);
    staticVial = world->CreateBody(&bodyDef);

    staticVial->SetLinearDamping(3.0f);
    staticVial->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-2.0f, -2.75f); //bottom-left
    vertices[1].Set(-2.0f, 2.75f); //top-left
    vertices[2].Set(2.0f, 2.75f); //top-right
    vertices[3].Set(2.0f, -2.75f); //bottom-right

    createWall(staticVial, vertices[0], vertices[1]); // Left wall
    createWall(staticVial, vertices[2], vertices[3]); // Right wall
    createWall(staticVial, vertices[0], vertices[3]); // Bottom wall
}

void MixingLogic::createStirRod()
{
    // Define a body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody; // Set the body to be dynamic
    bodyDef.position.Set(windowWidth  / 2 / SCALE, windowHeight / 10.25 / SCALE);
    b2Body *body = world->CreateBody(&bodyDef);

    // Assign a rectangular shape to the body
    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.05f, 1.75f);

    // Define fixture
    b2FixtureDef fixture;
    fixture.shape = &boxShape; // Assign shape to fixture
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.restitution = 0.3f;

    // Attach the fixture to the body
    body->CreateFixture(&fixture);

    body->SetAngularVelocity(2.0f);
}

void MixingLogic::createWall(b2Body* body, b2Vec2 vertex1, b2Vec2 vertex2)
{
    b2PolygonShape wall;
    float thickness = 0.1f;
    b2Vec2 direction = vertex2 - vertex1;
    b2Vec2 offset(direction.y, -direction.x);
    offset.Normalize();
    offset *= thickness / 2;
    b2Vec2 vertices[4] = {vertex1 - offset, vertex2 - offset, vertex2 + offset, vertex1 + offset};
    wall.Set(vertices, 4);

    createFixutre(body, &wall, 1.0f, 0.3f, 0.3f);
}

void MixingLogic::createNewWorld()
{
    b2Vec2 gravity(0.0f, -10.0f);
    if(world != nullptr)
    {
        delete world;
        world = nullptr;
    }
    world = new b2World(gravity);
    world->SetContactListener(&contact);
}

void MixingLogic::spawnCircle(chemicalBox2D* chemicalBox2D, b2Body* vial)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 vialPosition = vial->GetWorldCenter();
    bodyDef.position.Set(vialPosition.x, vialPosition.y);
    b2Body* particle = world->CreateBody(&bodyDef);
    particle->SetUserData((void*)chemicalBox2D);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;

    createFixutre(particle, &dynamicCircle, 1.0f, 0.1f, 0.01f);
}

void MixingLogic::spawnGas(b2Body* circle)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 circlePos = circle->GetWorldCenter();
    bodyDef.position.Set(circlePos.x, circlePos.y);
    b2Body* particle = world->CreateBody(&bodyDef);
    particle->SetGravityScale(-1);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.filter.categoryBits = 0;
    createFixutre(particle, &dynamicCircle, 1.0f, 0.1f, 0.01f);
}

b2Body* MixingLogic::getVial() const
{
    return vial;
}

b2Body* MixingLogic::getStaticVial() const
{
    return staticVial;
}

void MixingLogic::setVial(b2Body* otherVial)
{
    vial = otherVial;
}

void MixingLogic::setStaticVial(b2Body* otherVial)
{
    staticVial = otherVial;
}

b2World* MixingLogic::getWorld() const
{
    return world;
}

void MixingLogic::createFixutre(b2Body* body, b2Shape* shape, float32 density, float32 friction, float restitution)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    body->CreateFixture(&fixtureDef);
}

MixingLogic::~MixingLogic()
{
    delete world;
}
