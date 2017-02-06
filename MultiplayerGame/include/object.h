#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "collisioncallback.h"

/**
 * Struct
 * My vector
 */
struct Vec2 
{
	float32 X;
	float32 Y;
	Vec2(float32 x, float32 y) {
		X = x;
		Y = y;
	}
};
/**
 * Enum
 * Differentiate static and dinamic
 */

enum BodyType 
{
	kBodyType_Static = b2BodyType::b2_kinematicBody,
	kBodyType_Dynamic = b2BodyType::b2_dynamicBody,
};


/**
* Enum
* Differentiate objects
*/
enum DefineType
{
	kDefineType_Object,
	kDefineType_Player,
	kDefineType_Platform,
	kDefineType_Ground,
	kDefineType_Wall,
	kDefineType_SpikeBox,
	kDefineType_NetPlayer,
	kDefineType_Coin,
};

class Object {
public:
    /// Desstructor
	Object(Vec2 position,Vec2 scale,BodyType type,float32 density,
		  float32 friction,char* texture,Vec2 spriteOrigin);
    /// Constructor
	~Object() {};
	/// Init
	virtual void Init() {};
	/// Input
	virtual void Input() {};
	/// Update
	virtual void Update();
	/// Collision
	virtual void Collision(Object* instigator) {};
	/// Type of Object
	virtual DefineType getDefineType() { return kDefineType_Object; };
	/// Reset
	virtual void Reset();
	/// Render
	void Render();
	/// Body
	b2Body* Body;

protected:
	/// Get Position
	Vec2 GetPosition();
	/// Get Rotation
	float32 GetRotation();
	/**
	* Set a position
	* @param pos x and y.
	* @angle angle.
	*/
	void SetPosition(Vec2 pos, float32 angle);
	/**
	* Set a rotation
	* @param rot rotation.
	*/
	void SetRotation(float32 rot) {};

private:
	/// Texture
	sf::Texture Texture;
	/// Sprite
	sf::Sprite LastSprite;
	/// Position Sprite
	b2Vec2 SpriteOrigin;
	/// Input
	float32 InputValue;
	/// Collision  CallBack
	CollisionCallBack CollisionCallBack;
};

#endif //__OBJECT_H__
