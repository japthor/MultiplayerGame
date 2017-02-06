#ifndef __WALL_H__
#define __WALL_H__

#include "object.h"

class Wall : public Object {
public:
    /// Destructor
	~Wall() {};
    /// Constructor
	Wall(Vec2 position, Vec2 scale, BodyType type, float32 density,
		float32 friction, char* texture, Vec2 spriteOrigin);
	/// Init
	virtual void Init()  override {};
	/// Input
	virtual void Input() override {};
	/// Update
	virtual void Update() override {};
	/**
	* Collision with other objects
	* @param instigator Objects name to collide with.
	*/
	virtual void Collision(Object* instigator) override {};
	/// Type of Object
	virtual DefineType getDefineType() override;

};

#endif //__WaLL_H__

