#include "ground.h"

Ground::Ground(Vec2 position, Vec2 scale, BodyType type, float32 density, 
							 float32 friction, char * texture, Vec2 spriteOrigin) :Object(position,
							 scale, type, density, friction, texture, spriteOrigin)
{
	Body->SetUserData(this); 
}

DefineType Ground::getDefineType()
{
	return kDefineType_Ground;
}
