#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class myContactListener : public b2ContactListener
{
    /// @brief Checks for collisions among circles
    /// @param contact The items in contact
    virtual void BeginContact(b2Contact* contact);
};

#endif // CONTACTLISTENER_H
