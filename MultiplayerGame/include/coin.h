#ifndef __COIN_H__
#define __COIN_H__

#include "object.h"

class Coin : public Object {
public:
    /// Destructor
	~Coin() {};
    /// Constructor
	Coin(Vec2 position, Vec2 scale, BodyType type, float32 density,
		float32 friction, char* texture, Vec2 spriteOrigin);

	/// Init
	virtual void Init()  override {};
	/// Input
	virtual void Input() override {};
	/// Update
	virtual void Update() override;
	/// Reset
	virtual void Reset() override;
	/**
	* Collision with other objects
	* @param instigator Objects name to collide with.
	*/
	virtual void Collision(Object* instigator) override;
	/// Type of object
	virtual DefineType getDefineType() override;
	/// Move
	void Move();

private:
	/// Control if somebody capture the coin
	bool IsCapture;
	/// Random for next position.
	int WhereToMove;

};

#endif //__WaLL_H__
