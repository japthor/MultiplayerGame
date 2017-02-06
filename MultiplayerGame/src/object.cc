#include "object.h"
#include "assets.h"
#include "gamemanager.h"

#define SCALE 30.0f

Object::Object(Vec2 position,Vec2 scale,BodyType type,float32 density,
               float32 friction,char* texture,Vec2 spriteOrigin)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(position.X / SCALE, position.Y / SCALE);
    
    if (type == BodyType::kBodyType_Static)
        bodyDef.type = b2_staticBody;
    else if(type == BodyType::kBodyType_Dynamic)
        bodyDef.type = b2_dynamicBody;
    
    Body = GameManager::GetInstance()->GetWorld()->CreateBody(&bodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox((scale.X / 2.0f) / SCALE, (scale.Y / 2.0f) / SCALE);
    
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.density = friction;
    fixtureDef.shape = &shape;
    Body->CreateFixture(&fixtureDef);
    
    
    Texture.loadFromFile(ASSETS::ImagePath(texture).c_str());
    
    SpriteOrigin = b2Vec2(spriteOrigin.X, spriteOrigin.Y);
    
    GameManager::GetInstance()->GetWorld()->SetContactListener(&CollisionCallBack);
}


void Object::Update()
{
    
}

void Object::Reset()
{
}

void Object::Render()
{
    
    sf::Sprite sprite;
    sprite.setTexture(Texture);
    sprite.setOrigin(SpriteOrigin.x, SpriteOrigin.y);
    
    Vec2 pos = GetPosition();
    sprite.setPosition(pos.X, pos.Y);
    sprite.setRotation(GetRotation());
    
    LastSprite = sprite;
    
    GameManager::GetInstance()->GetWindow()->draw(LastSprite);
}

Vec2 Object::GetPosition()
{
    Vec2 result = Vec2(Body->GetPosition().x * SCALE, Body->GetPosition().y * SCALE);
    return Vec2(result);
}

float32 Object::GetRotation()
{
    float32 result;
    
    if (Body->GetType() == b2_staticBody)
        result = (180 / b2_pi * Body->GetAngle());
    else if (Body->GetType() == b2_dynamicBody)
        result = (Body->GetAngle() * 180 / b2_pi);
    
    return result;
}

void Object::SetPosition(Vec2 pos , float32 angle)
{
    Body->SetTransform(b2Vec2(pos.X / SCALE,pos.Y / SCALE), angle / (180 / b2_pi));
}





