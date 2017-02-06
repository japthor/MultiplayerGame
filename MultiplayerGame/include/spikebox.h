#ifndef __SPIKEBOX_H__
#define __SPIKEBOX_H__

#include "object.h"

class SpikeBox : public Object {
public:
    /// Destructor
	~SpikeBox() {};
    /// Constructor
	SpikeBox(Vec2 position, Vec2 scale, BodyType type, float32 density,
		       float32 friction, char* texture, Vec2 spriteOrigin);
	/// Init
	virtual void Init()  override {};
	/// Input
	virtual void Input() override {};
	/// Update
	virtual void Update()override;
	/// Reset
	virtual void Reset() override;
	/**
	* Collision with other objects
	* @param instigator Objects name to collide with.
	*/	
	virtual void Collision(Object* instigator) override;
	/// Type of object
	virtual DefineType getDefineType() override;

private:
	/// Velocity X
	int ChangeVelocityX;

};

#endif //__SPIKEBOX_H__
