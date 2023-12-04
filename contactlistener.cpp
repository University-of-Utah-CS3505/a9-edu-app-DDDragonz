#include "contactlistener.h"
#include "chemical.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

void myContactListener::BeginContact(b2Contact* contact)
{
    void* dataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* dataB = contact->GetFixtureB()->GetBody()->GetUserData();

    // int i = *static_cast<int*>(dataA);
    if(dataA && dataB)
    {
        Chemical* a = static_cast<Chemical*>(dataA);
        Chemical* b = static_cast<Chemical*>(dataB);
        if(a->s_id != b->s_id)
        {
            // qDebug() << "contact";
            // a->s_color = Qt::black;
            a->s_touch = true;
            b->s_touch = true;
        }
    }

}
