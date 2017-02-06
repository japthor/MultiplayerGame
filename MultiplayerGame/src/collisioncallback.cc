#include "collisioncallback.h"
#include "Object.h"

void CollisionCallBack::BeginContact(b2Contact * contact)
{
	Object* ob;
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData) 
	{
		ob = static_cast<Object*>(bodyUserData);
		ob->Collision(static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData()));
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		ob = static_cast<Object*>(bodyUserData);
		ob->Collision(static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData()));
	}
}


