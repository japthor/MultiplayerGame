#include "coin.h"
#include "networkmanager.h"

static CoinInfo info;

Coin::Coin(Vec2 position, Vec2 scale, BodyType type, float32 density,
           float32 friction, char * texture, Vec2 spriteOrigin) :Object(position,
                                                                        scale, type, density, friction, texture, spriteOrigin)
{
    Body->SetUserData(this);
    Body->SetGravityScale(0.0f);
    IsCapture = false;
    WhereToMove = 0;
}

void Coin::Update()
{
    Body->SetLinearVelocity(b2Vec2(0, 0));
    Body->SetAngularVelocity(0);
    bool otherPlayerCapture = NetWorkManager::GetInstance()->ReceiveGameInfoTCP();
    
    if (IsCapture) {
        Move();
        NetWorkManager::GetInstance()->AddPoints(1);

				info.PosX = this->GetPosition().X;
				info.PosY = this->GetPosition().Y;
				info.Rotation = this->GetRotation();

				NetWorkManager::GetInstance()->SendGameInfoTCP(&info);
        
        if (NetWorkManager::GetInstance()->GetPoints() >= 10) {
            NetWorkManager::GetInstance()->SendVictoryUDP();
            
        }
        
    }

		static int num = 0;
		num++;

		if (NetWorkManager::GetInstance()->PlayerIndex == 0 && num > 30) {
			info.PosX = this->GetPosition().X;
			info.PosY = this->GetPosition().Y;
			info.Rotation = this->GetRotation();
			NetWorkManager::GetInstance()->SendGameInfoTCP(&info);
			num -= 30;
		}


    
    if (otherPlayerCapture) {
        SetPosition(Vec2(NetWorkManager::GetInstance()->Coin.PosX, NetWorkManager::GetInstance()->Coin.PosY), NetWorkManager::GetInstance()->Coin.Rotation);
    }
}

void Coin::Reset()
{
    this->SetPosition(Vec2(390.0f, 320.0f), this->GetRotation());

		info.PosX = this->GetPosition().X;
		info.PosY = this->GetPosition().Y;
		info.Rotation = this->GetRotation();

		NetWorkManager::GetInstance()->SendGameInfoTCP(&info);
}

void Coin::Collision(Object * instigator)
{
    if (instigator != nullptr) {
        if (instigator->getDefineType() == kDefineType_Player)
            IsCapture = true;
    }
}

DefineType Coin::getDefineType()
{
    return kDefineType_Coin;
}

void Coin::Move()
{
    int newPoint = 0 + (rand() % (int)(3 - 0 + 1));
    
    while(newPoint == WhereToMove)
        newPoint = 0 + (rand() % (int)(3 - 0 + 1));
    
    WhereToMove = newPoint;
    
    switch (WhereToMove)
    {
        case 0:
            this->SetPosition(Vec2(390.0f, 320.0f), this->GetRotation());
            break;
        case 1:
            this->SetPosition(Vec2(390.0f, 100.0f), this->GetRotation());
            break;
        case 2:
            this->SetPosition(Vec2(560.0f, 470.0f), this->GetRotation());
            break;
        case 3:
            this->SetPosition(Vec2(230.0f, 470.0f), this->GetRotation());
            break;
            
        default:
            break;
    }
    
    IsCapture = false;
}
