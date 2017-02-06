#ifndef __NETPLAYER_H__
#define __NETPLAYER_H__

#include "object.h"
#include "networkmanager.h"

/// Number of net players
static int NumNetPlayers = 0;

class NetPlayer : public Object {
public:
    /// Destructor
	~NetPlayer() {};
    /// Constructor
	NetPlayer(Vec2 position, Vec2 scale, BodyType type, float32 density,
			  float32 friction, char* texture, Vec2 spriteOrigin);
	/// Init
	virtual void Init()  override {};
	/// Input
	virtual void Input() override {};
	/// Update
	virtual void Update() override;
	/// Type of object
	virtual DefineType getDefineType() override;

private:
	/// Controls number of players.
	int Index;
	
};

#endif //__NETPLAYER_H__
