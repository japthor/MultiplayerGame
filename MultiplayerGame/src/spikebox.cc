#include "spikebox.h"
#include "networkmanager.h"

static SpikeBoxInfo info;

SpikeBox::SpikeBox(Vec2 position, Vec2 scale, BodyType type, float32 density,
                   float32 friction, char * texture, Vec2 spriteOrigin) :Object(position,
                                                                                scale, type, density, friction, texture, spriteOrigin)
{
    Body->SetUserData(this);
    ChangeVelocityX = 10;
}

void SpikeBox::Update()
{
    if(NetWorkManager::GetInstance()->PlayerIndex == 0)
    {
        if (this->GetPosition().X > (800.0f - 70.0f - 1.0f))
            ChangeVelocityX = -10;
        
        if (this->GetPosition().X < (0.0f + 70.0f + 1.0f))
            ChangeVelocityX = 10;
        
        b2Vec2 vel = Body->GetLinearVelocity();
        float velChange = ChangeVelocityX - vel.x;
        float force = Body->GetMass()* velChange / (1 / 60.0f);
        Body->ApplyForce(b2Vec2(force, 0), Body->GetWorldCenter(), true);
        
        info.PosX = this->GetPosition().X;
        info.PosY = this->GetPosition().Y;
        info.Rotation = this->GetRotation();
        
        NetWorkManager::GetInstance()->SendSpikeBoxInfoUDP(&info);
    }
    else
    {
        NetWorkManager::GetInstance()->ReceiveGameInfoUDP();
        this->SetPosition(Vec2(NetWorkManager::GetInstance()->SpikeBox.PosX, NetWorkManager::GetInstance()->SpikeBox.PosY), NetWorkManager::GetInstance()->SpikeBox.Rotation);
    }	
}

void SpikeBox::Reset()
{
    this->SetPosition(Vec2(465.0f, 536.0f), this->GetRotation());
}

void SpikeBox::Collision(Object * instigator)
{
    
}

DefineType SpikeBox::getDefineType()
{
    return kDefineType_SpikeBox;
}

