#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class myContactListener : public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact);
};

#endif // CONTACTLISTENER_H
