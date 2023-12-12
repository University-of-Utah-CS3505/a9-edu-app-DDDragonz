#include "contactlistener.h"
#include "mixingchemical.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

void myContactListener::BeginContact(b2Contact* contact)
{
    void* dataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* dataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if(dataA && dataB)
    {
        MixingChemical* a = static_cast<MixingChemical*>(dataA);
        MixingChemical* b = static_cast<MixingChemical*>(dataB);
        if(a->s_id != b->s_id)
        {
            a->s_touch = true;
            b->s_touch = true;
        }
    }
}
