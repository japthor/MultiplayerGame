#include "netplayer.h"

NetPlayer::NetPlayer(Vec2 position, Vec2 scale, BodyType type, float32 density,
					 float32 friction, char* texture, Vec2 spriteOrigin) :Object(position,
					 scale, type, density, friction, texture, spriteOrigin) {

	Body->SetUserData(this);
	Index = 0;
	Index = NumNetPlayers;
	NumNetPlayers++;
}
void NetPlayer::Update()
{
	if (NetWorkManager::GetInstance()->PlayerIndex != Index) {
		SetPosition(Vec2(NetWorkManager::GetInstance()->Players[Index].PosX, NetWorkManager::GetInstance()->Players[Index].PosY),
			NetWorkManager::GetInstance()->Players[Index].Rotation);
	}
	else {
		SetPosition(Vec2(-1000.0f,-1000.0f),0.0f);
	}
}

DefineType NetPlayer::getDefineType()
{
	return kDefineType_NetPlayer;
}
