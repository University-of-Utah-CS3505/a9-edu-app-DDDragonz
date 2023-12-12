#include "mixinglogic.h"
#include "contactlistener.h"
#include "mixingchemical.h"

MixingLogic::MixingLogic(float width, float height, float scale) :
    m_worldScale(scale),
    m_windowWidth(width),
    m_windowHeight(height),
    m_logicWorld(new b2World(b2Vec2(0.0f, -10.0f)))
{
    m_logicWorld->SetContactListener(&m_contact);
    m_isVialDrawn = false;
}

void MixingLogic::createBorder()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(0, 0);
    b2Body* body = m_logicWorld->CreateBody(&bodyDef);

    float generalOffSet = 3.0f;
    b2EdgeShape edge;

    // Bottom border
    edge.Set(b2Vec2(0, 0), b2Vec2((m_windowWidth + generalOffSet) / m_worldScale, 0));
    body->CreateFixture(&edge, 0);

    // Top border
    edge.Set(b2Vec2(0, (m_windowHeight) / m_worldScale), b2Vec2((m_windowWidth + generalOffSet) / m_worldScale, (m_windowHeight) / m_worldScale));
    body->CreateFixture(&edge, 0);

    // Left border
    edge.Set(b2Vec2(0, -generalOffSet / m_worldScale), b2Vec2(0, (m_windowHeight + generalOffSet) / m_worldScale));
    body->CreateFixture(&edge, 0);

    // Right border
    edge.Set(b2Vec2((m_windowWidth + generalOffSet) / m_worldScale, -generalOffSet / m_worldScale), b2Vec2((m_windowWidth + generalOffSet) / m_worldScale, (m_windowHeight + generalOffSet) / m_worldScale));
    body->CreateFixture(&edge, 0);
}

void MixingLogic::createVial()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;

    bodyDef.position.Set(m_windowWidth  / 4 / m_worldScale, m_windowHeight / 3 / m_worldScale);
    m_vial = m_logicWorld->CreateBody(&bodyDef);
    m_vial->SetLinearDamping(3.0f);
    m_vial->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-1.0f, -3.0f); //bottom-left
    vertices[1].Set(-1.0f, 3.0f); //top-left
    vertices[2].Set(1.0f, 3.0f); //top-right
    vertices[3].Set(1.0f, -3.0f); //bottom-right

    createWall(m_vial, vertices[0], vertices[1]); // Left wall
    createWall(m_vial, vertices[2], vertices[3]); // Right wall
    createWall(m_vial, vertices[0], vertices[3]); // Bottom wall
}

void MixingLogic::createBeaker()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.position.Set(m_windowWidth  / 2 / m_worldScale, m_windowHeight / 5 / m_worldScale - 0.2);
    m_beaker = m_logicWorld->CreateBody(&bodyDef);

    m_beaker->SetLinearDamping(3.0f);
    m_beaker->SetAngularDamping(3.0f);

    b2Vec2 vertices[4];
    vertices[0].Set(-2.0f, -2.75f); //bottom-left
    vertices[1].Set(-2.0f, 2.75f); //top-left
    vertices[2].Set(2.0f, 2.75f); //top-right
    vertices[3].Set(2.0f, -2.75f); //bottom-right

    createWall(m_beaker, vertices[0], vertices[1]); // Left wall
    createWall(m_beaker, vertices[2], vertices[3]); // Right wall
    createWall(m_beaker, vertices[0], vertices[3]); // Bottom wall
}

void MixingLogic::createStirRod()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;

    b2Vec2 beakerPosition = m_beaker->GetPosition();
    bodyDef.position.Set(beakerPosition.x, beakerPosition.y - 1.0f);
    b2Body *body = m_logicWorld->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.05f, 1.75f);
    createFixutre(body, &boxShape, 1.0f, 0.3f, 0.3f, false);
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

    createFixutre(body, &wall, 1.0f, 0.3f, 0.3f, false);
}

void MixingLogic::createNewWorld()
{
    b2Vec2 gravity(0.0f, -10.0f);
    if(m_logicWorld != nullptr)
    {
        delete m_logicWorld;
        m_logicWorld = nullptr;
    }
    m_logicWorld = new b2World(gravity);
    m_logicWorld->SetContactListener(&m_contact);
}

void MixingLogic::spawnCircle(MixingChemical* chemical, b2Body* vial)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 vialPosition = vial->GetWorldCenter();
    bodyDef.position.Set(vialPosition.x, vialPosition.y);
    b2Body* particle = m_logicWorld->CreateBody(&bodyDef);
    particle->SetUserData((void*)chemical);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;
    createFixutre(particle, &dynamicCircle, 1.0f, 0.1f, 0.01f, false);
}

void MixingLogic::spawnGas(b2Body* circle)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 circlePos = circle->GetWorldCenter();
    bodyDef.position.Set(circlePos.x, circlePos.y);
    b2Body* particle = m_logicWorld->CreateBody(&bodyDef);
    particle->SetGravityScale(-1);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 0.1f;
    createFixutre(particle, &dynamicCircle, 1.0f, 0.1f, 0.01f, true);
}

void MixingLogic::spawnSolid(b2Body* circle)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 2.0f;
    bodyDef.angularDamping = 1.0f;

    b2Vec2 circlePos = circle->GetWorldCenter();
    bodyDef.position.Set(circlePos.x, circlePos.y);
    b2Body* particle = m_logicWorld->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.05f, 0.05f);
    createFixutre(particle, &boxShape, 6.0f, 0.9f, 0.0f, false);
}

void MixingLogic::setWindowWidth(int newWidth)
{
    m_windowWidth = newWidth;
}

void MixingLogic::setWindowHeight(int newHeight)
{
    m_windowHeight = newHeight;
}

void MixingLogic::setWorldScale(float newScale)
{
    m_worldScale = newScale;
}

b2Body* MixingLogic::getVial() const
{
    return m_vial;
}

b2Body* MixingLogic::getBeaker() const
{
    return m_beaker;
}

void MixingLogic::setVial(b2Body* otherVial)
{
    m_vial = otherVial;
}

void MixingLogic::setBeaker(b2Body* otherBeaker)
{
    m_beaker = otherBeaker;
}

b2World* MixingLogic::getWorld() const
{
    return m_logicWorld;
}

bool MixingLogic::getIsVialDrawn()
{
    return m_isVialDrawn;
}

void MixingLogic::setIsVialDrawn(bool state)
{
    m_isVialDrawn = state;
}

void MixingLogic::createFixutre(b2Body* body, b2Shape* shape, float density, float friction, float restitution, bool collisions)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    if(collisions)
    {
        fixtureDef.filter.categoryBits = 0;
    }
    body->CreateFixture(&fixtureDef);
}

MixingLogic::~MixingLogic()
{
    delete m_logicWorld;
}
