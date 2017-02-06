#ifndef __GROUND_H__
#define __GROUND_H__

#include "object.h"

class Ground : public Object {
public:
    /// Destructor
	~Ground() {};
    /// Constructor
	Ground(Vec2 position, Vec2 scale, BodyType type, float32 density,
		     float32 friction, char* texture, Vec2 spriteOrigin);
	/// Init
	virtual void Init()  override {};
	/// Input
	virtual void Input() override {};
	/// Update
	virtual void Update() override {};
	/// Type of object
	virtual DefineType getDefineType() override;

};

#endif //__GROUND_H__

