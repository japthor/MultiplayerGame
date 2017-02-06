#ifndef __COLLISIONCALLBACK_H__
#define __COLLISIONCALLBACK_H__

#include <Box2D/Box2D.h>

class CollisionCallBack: public b2ContactListener {
public:
	
	/// Box2D collision start listener.
	virtual void BeginContact(b2Contact* contact) override;
	/// Box2D collision end listener.
	virtual void EndContact(b2Contact* contact) override {};

private:

};

#endif //__COLLISIONCALLBACK_H__
