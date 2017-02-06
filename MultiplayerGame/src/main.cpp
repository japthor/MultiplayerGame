#include "gamemanager.h"
#include "player.h"

Player* player;

void Init()
{
    GameManager::GetInstance()->Init();
    
    // Player Shadow
    GameManager::GetInstance()->CreateObject(Vec2(64.0f, -64.0f), Vec2(64.0f, 64.0f), kBodyType_Static, 0.15f, 0.25f, "Blue.png", Vec2(32.0f, 32.0f), kDefineType_NetPlayer);
    // Player Shadow
    GameManager::GetInstance()->CreateObject(Vec2(64.0f, -64.0f), Vec2(64.0f, 64.0f), kBodyType_Static, 0.15f, 0.25f, "Brown.png", Vec2(32.0f, 32.0f), kDefineType_NetPlayer);
    // Player Shadow
    GameManager::GetInstance()->CreateObject(Vec2(64.0f, -64.0f), Vec2(64.0f, 64.0f), kBodyType_Static, 0.15f, 0.25f, "Green.png", Vec2(32.0f, 32.0f), kDefineType_NetPlayer);
    // Player Shadow
    GameManager::GetInstance()->CreateObject(Vec2(64.0f, -64.0f), Vec2(64.0f, 64.0f), kBodyType_Static, 0.15f, 0.25f, "Pink.png", Vec2(32.0f, 32.0f), kDefineType_NetPlayer);
    // Player
    player = (Player*)GameManager::GetInstance()->CreateObject(Vec2(64.0f , 160.0f), Vec2(64.0f, 64.0f), kBodyType_Dynamic, 0.15f, 0.25f, "Orange.png", Vec2(32.0f, 32.0f),kDefineType_Player);
    // Up & Down Ground
    GameManager::GetInstance()->CreateObject(Vec2(400.0f, 584.0f), Vec2(800.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "Ground.png", Vec2(400.0f, 16.0f), kDefineType_Ground);
    GameManager::GetInstance()->CreateObject(Vec2(400.0f, 16.0f), Vec2(800.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "Ground.png", Vec2(400.0f, 16.0f), kDefineType_Wall);
    // Left & Right Ground
    GameManager::GetInstance()->CreateObject(Vec2(16.0f, 260.0f), Vec2(32.0f, 800.0f), kBodyType_Static, 0.0f, 0.0f, "Ground2.png", Vec2(16.0f, 400.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(784.0f, 260.0f), Vec2(32.0f, 800.0f), kBodyType_Static, 0.0f, 0.0f, "Ground2.png", Vec2(16.0f, 400.0f), kDefineType_Wall);
    // Platform
    GameManager::GetInstance()->CreateObject(Vec2(230.0f, 410.0f), Vec2(200.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "Platform.png", Vec2(100.0f, 16.0f), kDefineType_Platform);
    GameManager::GetInstance()->CreateObject(Vec2(560.0f, 410.0f), Vec2(200.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "Platform.png", Vec2(100.0f, 16.0f), kDefineType_Platform);
    GameManager::GetInstance()->CreateObject(Vec2(390.0f, 230.0f), Vec2(200.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "Platform.png", Vec2(100.0f, 16.0f), kDefineType_Platform);
    // Platform Wall
    GameManager::GetInstance()->CreateObject(Vec2(130.0f, 410.0f), Vec2(10.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall.png", Vec2(5.0f, 16.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(330.0f, 410.0f), Vec2(10.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall.png", Vec2(5.0f, 16.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(460.0f, 410.0f), Vec2(10.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall.png", Vec2(5.0f, 16.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(660.0f, 410.0f), Vec2(10.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall.png", Vec2(5.0f, 16.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(290.0f, 230.0f), Vec2(10.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall.png", Vec2(5.0f, 16.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(490.0f, 230.0f), Vec2(10.0f, 32.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall.png", Vec2(5.0f, 16.0f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(230.0f, 422.0f), Vec2(200.0f, 9.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall2.png", Vec2(100.0f, 4.5f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(560.0f, 422.0f), Vec2(200.0f, 9.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall2.png", Vec2(100.0f, 4.5f), kDefineType_Wall);
    GameManager::GetInstance()->CreateObject(Vec2(390.0f, 242.0f), Vec2(200.0f, 9.0f), kBodyType_Static, 0.0f, 0.0f, "PlatformWall2.png", Vec2(100.0f, 4.5f), kDefineType_Wall);
    // SpikeBox
    GameManager::GetInstance()->CreateObject(Vec2(465.0f, 536.0f), Vec2(50.0f, 50.0f), kBodyType_Dynamic, 0.0f, 0.0f, "SpikeBox.png", Vec2(25.0f, 25.0f), kDefineType_SpikeBox);
    // Coin
    GameManager::GetInstance()->CreateObject(Vec2(390.0f, 320.0f), Vec2(32.0f, 32.0f), kBodyType_Dynamic, 0.0f, 0.0f, "Coin.png", Vec2(16.0f, 16.0f), kDefineType_Coin);
    
    GameManager::GetInstance()->Reset();
}

void Input(GameManager* GM)
{
    GM->Input();
}

void Update(GameManager* GM)
{
    GM->Update();
}

void Render(GameManager* GM)
{
    GM->Render();
}

int main() {
    GameManager* GM = GameManager::GetInstance();
    Init();
    
    while (GM->GetWindow()->isOpen()) {
        Input(GM);
        Update(GM);
        Render(GM);
    }
    
    if (Scene::GetInstance()->GetScene() == kSceneType_Game) {
        player->Disappear();
    }
    GameManager::GetInstance()->ShutDownIMGUI();
    return EXIT_SUCCESS;
}
