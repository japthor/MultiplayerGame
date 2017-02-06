#include "player.h"
#include "networkmanager.h"
#include "gamemanager.h"

static PlayerInfo info;

Player::Player(Vec2 position, Vec2 scale, BodyType type, float32 density, float32 friction, char * texture, Vec2 spriteOrigin):Object(position,
                                                                                                                                      scale, type, density, friction, texture, spriteOrigin)
{
    Body->SetUserData(this);
    IsDPressed = false;
    IsAPressed = false;
    IsSpacePressed = false;
    IsJumping = false;
    IsKilled = false;
}

void Player::Input()
{
    if(GameManager::GetInstance()->GetWindow()->hasFocus()){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            IsDPressed = true;
        else
            IsDPressed = false;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            IsAPressed = true;
        else
            IsAPressed = false;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (!IsJumping)
            {
                IsSpacePressed = true;
                IsJumping = true;
            }
            else
                IsSpacePressed = false;
        }
        else
            IsSpacePressed = false;
    }
}

void Player::Update()
{
    //										  Width    Player   Difference
    if (IsDPressed && this->GetPosition().X < (800.0f - 64.0f - 1.0f))
    {
        b2Vec2 vel = Body->GetLinearVelocity();
        float32 velChange = 5.0f - vel.x;
        float32 force = Body->GetMass()* velChange / (1 / 60.0f);
        Body->ApplyForce(b2Vec2(force, 0), Body->GetWorldCenter(), true);
    }
    else if (IsAPressed && this->GetPosition().X >(0.0f + 64.0f + 1.0f))
    {
        b2Vec2 vel = Body->GetLinearVelocity();
        float32 velChange = -5.0f - vel.x;
        float32 force = Body->GetMass()* velChange / (1 / 60.0f);
        Body->ApplyForce(b2Vec2(force, 0), Body->GetWorldCenter(), true);
    }
    
    if (IsSpacePressed)
    {
        b2Vec2 vel = Body->GetLinearVelocity();
        float32 inputValue = 12.0f;
        float32 velChange = -inputValue - vel.y;
        float32 impulse = Body->GetMass() * velChange;
        Body->ApplyLinearImpulse(b2Vec2(0.0f, impulse), Body->GetWorldCenter(), true);
        
    }
    
    if (this->GetPosition().X >= 800 || this->GetPosition().X <= 0) {
        this->SetPosition(Vec2(64.0f, 64.0f), this->GetRotation());
    }
    
    if (this->GetPosition().Y <= 0 || this->GetPosition().Y >= 600) {
        this->SetPosition(Vec2(64.0f, 64.0f), this->GetRotation());
    }
    
    info.PosX = this->GetPosition().X;
    info.PosY = this->GetPosition().Y;
    info.Rotation = this->GetRotation();
		info.Points = NetWorkManager::GetInstance()->GetPoints();
    
    NetWorkManager::GetInstance()->SendPlayerInfoUDP(&info);
    NetWorkManager::GetInstance()->ReceiveGameInfoUDP();
    
    if (IsKilled) {
        Kill();
    }
}

void Player::Collision(Object* instigator)
{
    if (instigator != nullptr) {
        if ((instigator->getDefineType() == kDefineType_Platform || instigator->getDefineType() == kDefineType_Ground) || instigator->getDefineType() == kDefineType_NetPlayer)
            IsJumping = false;
        
        if (instigator->getDefineType() == kDefineType_SpikeBox) {
            IsKilled = true;
            NetWorkManager::GetInstance()->SubtractPoints(3);
        }
    }
}

void Player::Reset()
{
    this->SetPosition(Vec2(64.0f, 160.0f), this->GetRotation());
    IsKilled = false;
}

void Player::Kill()
{
    this->SetPosition(Vec2(64.0f, 100.0f), this->GetRotation());
    IsKilled = false;
}

void Player::Disappear() {
    info.PosX = -1000.0f;
    info.PosY = this->GetPosition().Y;
    info.Rotation = this->GetRotation();
    
    NetWorkManager::GetInstance()->SendPlayerInfoUDP(&info);
}

