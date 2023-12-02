#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "qdebug.h"
#include <Box2D/Dynamics/b2WorldCallbacks.h>



class myContactListener : public b2ContactListener
{
    virtual void BeginContact(b2Contact* contact);

    //    void EndContact(b2Contact* contact) {
    //        qDebug() << "contact";


    //       /* //check if fixture A was a ball
    //        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    //        if ( bodyUserData )
    //            static_cast<Ball*>( bodyUserData )->endContact();

    //        //check if fixture B was a ball
    //        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    //        if ( bodyUserData )
    //            static_cast<Ball*>( bodyUserData )->endContact(); */

    //    }
};

#endif // CONTACTLISTENER_H
