#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "object.h"

class Player : public Object {
public:
    /// Destructor
    ~Player() {};
    /// Constructor
    Player(Vec2 position, Vec2 scale, BodyType type, float32 density,
	  float32 friction, char* texture, Vec2 spriteOrigin);

	/// Init
    virtual void Init()  override{};
	/// Input
    virtual void Input() override;
	/// Update
    virtual void Update()override;
	/**
	* Collision with other objects
	* @param instigator Objects name to collide with.
	*/
    virtual void Collision(Object* instigator) override;
	/// Reset
	virtual void Reset()override;
	/// Kill
    void Kill();
	/// Type of Object
    virtual DefineType getDefineType() override { return kDefineType_Player; };
	/// Disappear if somebody disconnects
	void Disappear();

private:
	/// Is pressing D
	bool IsDPressed;
	/// Is pressing A
	bool IsAPressed;
	/// Is pressing Space
	bool IsSpacePressed;
	/// Is pressing Jump
	bool IsJumping;
	/// Player has been killed
	bool IsKilled;
};

#endif //__PLAYER_H__
