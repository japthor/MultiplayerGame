#include "wall.h"

Wall::Wall(Vec2 position, Vec2 scale, BodyType type, float32 density, 
					 float32 friction, char * texture, Vec2 spriteOrigin) :Object(position,
					 scale, type, density, friction, texture, spriteOrigin)
{
		Body->SetUserData(this);
}

DefineType Wall::getDefineType()
{
	return kDefineType_Wall;
}
