#include "contactlistener.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

void myContactListener::BeginContact(b2Contact* contact)
{
    contact->GetFixtureA()->GetBody();
    qDebug() << "contact";
}
