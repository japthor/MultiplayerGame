#include "gamemanager.h"
#include "player.h"
#include "platform.h"
#include "ground.h"
#include "wall.h"
#include "assets.h"
#include "spikebox.h"
#include "netplayer.h"
#include "coin.h"
#include "imgui.h"
#include "imgui-sfml.h"
#

GameManager* GameManager::Instance = nullptr;

GameManager* GameManager::GetInstance() {
    if (Instance == nullptr)
        Instance = new GameManager();
    
    return Instance;
}

void GameManager::Init() {
    Window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML window");
    Window->setFramerateLimit(60);
    
    World = new b2World(b2Vec2(0.0f, 9.8f));
    Window->resetGLStates();
    
    InitIMGUI();
    
    Scene::GetInstance()->CheckFiles();
    
    srand(time_t(NULL));
}

void GameManager::Input() {
    switch (Scene::GetInstance()->GetScene())
    {
        case kSceneType_MainMenu:
            Scene::GetInstance()->InputScene(kSceneType_MainMenu);
            break;
            
        case kSceneType_Game:
            for (unsigned int i = 0; i < Objects.size(); i++)
            {
                Objects[i]->Input();
            }
            
            break;
            
        default:
            break;
    }
    
}

void GameManager::Update() {
    sf::Event event;
    switch (Scene::GetInstance()->GetScene())
    {
        case kSceneType_MainMenu:
            while (Window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed) {
                    Window->close();
                }
            }
            if (Window->isOpen()) {
                Scene::GetInstance()->UpdateMainMenu();
            }
            break;
            
        case kSceneType_Game:
            while (Window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    Window->close();
                }
            }
            
            for (unsigned int i = 0; i < Objects.size(); i++)
            {
                Objects[i]->Update();
            }
            
            //Scene::GetInstance()->Update(kSceneType_Game);
            break;
            
        case kSceneType_GameOverWin:
            while (Window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed) {
                    Window->close();
                }
            }
            Scene::GetInstance()->UpdateGameOver();
            break;
            
        case kSceneType_GameOverLose:
            while (Window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed) {
                    Window->close();
                }
            }
            Scene::GetInstance()->UpdateGameOver();
            break;
            
        default:
            break;
    }
}

void GameManager::Render() {
    
    Window->clear(sf::Color::Black);
    
    switch (Scene::GetInstance()->GetScene())
    {
        case kSceneType_MainMenu:
            Scene::GetInstance()->DrawScene(kSceneType_MainMenu);
            
            break;
        case kSceneType_Game:
            for (unsigned int i = 0; i < Objects.size(); i++)
                Objects[i]->Render();
            
            Scene::GetInstance()->DrawScene(kSceneType_Game);
            Window->draw(Scene::GetInstance()->GetScoreText());
            Window->draw(Scene::GetInstance()->GetPoints());
						Window->draw(Scene::GetInstance()->GetInGameNameText());
						Window->draw(Scene::GetInstance()->GetInGameOtherUsersPointsText1());
						Window->draw(Scene::GetInstance()->GetInGameOtherUsersPointsText2());
						Window->draw(Scene::GetInstance()->GetInGameOtherUsersPointsText3());
						Window->draw(Scene::GetInstance()->GetInGameOtherUsersPointsText4());
            
            World->Step(1 / 60.0f, 8, 3);
            break;
            
        case kSceneType_GameOverWin:
            Scene::GetInstance()->DrawScene(kSceneType_GameOverWin);
            Window->draw(Scene::GetInstance()->GetGameOverTitle());
            Window->draw(Scene::GetInstance()->GetGameOverWinText());
            Window->draw(Scene::GetInstance()->GetGameOverWinnerNameText());
            Window->draw(Scene::GetInstance()->GetGameOverCongratulationsText());
            break;
            
        case kSceneType_GameOverLose:
            Scene::GetInstance()->DrawScene(kSceneType_GameOverLose);
            Window->draw(Scene::GetInstance()->GetGameOverTitle());
            Window->draw(Scene::GetInstance()->GetGameOverLoseText());
            Window->draw(Scene::GetInstance()->GetGameOverLoserNameText());
            Window->draw(Scene::GetInstance()->GetGameOverLoseWinnerText());
            break;
            
        default:
            break;
    }
    
    Window->display();
}

Object* GameManager::CreateObject(Vec2 position,Vec2 scale,BodyType type,float32 density,
                                  float32 friction,char* texture,Vec2 spriteOrigin,
                                  DefineType spawnType) {
    
    Object* NewObject = nullptr;
    
    switch (spawnType)
    {
        case kDefineType_Object:
            NewObject = new Object(position,scale,type,density,
                                   friction,texture,spriteOrigin);
            break;
        case kDefineType_Player:
            NewObject = new Player(position, scale, type, density,
                                   friction, texture, spriteOrigin);
            break;
        case kDefineType_Platform:
            NewObject = new Platform(position, scale, type, density,
                                     friction, texture, spriteOrigin);
            break;
        case kDefineType_Ground:
            NewObject = new Ground(position, scale, type, density,
                                   friction, texture, spriteOrigin);
            break;
        case kDefineType_Wall:
            NewObject = new Wall(position, scale, type, density,
                                 friction, texture, spriteOrigin);
            break;
            
        case kDefineType_SpikeBox:
            NewObject = new SpikeBox(position, scale, type, density,
                                     friction, texture, spriteOrigin);
            break;
            
        case kDefineType_NetPlayer:
            NewObject = new NetPlayer(position, scale, type, density,
                                      friction, texture, spriteOrigin);
            break;
            
        case kDefineType_Coin:
            NewObject = new Coin(position, scale, type, density,
                                 friction, texture, spriteOrigin);
            break;
            
        default:
            break;
    }
    Objects.push_back(NewObject);
    
    return NewObject;
}

void GameManager::Reset()
{
    NetWorkManager::GetInstance()->SetPoints(0);
    for (unsigned int i = 0; i < Objects.size(); i++)
        Objects[i]->Reset();
    
}

void GameManager::InitIMGUI()
{
    ImGui::SFML::Init(*Window);
}

void GameManager::UpdateIMGUI()
{
    ImGui::SFML::Update(*GameManager::GetInstance()->GetWindow(), GameManager::GetInstance()->deltaClock.restart());
}

void GameManager::RenderIMGUI()
{
    ImGui::Render();
}

void GameManager::EndIMGUI()
{
    ImGui::End();
}

void GameManager::ShutDownIMGUI()
{
    ImGui::SFML::Shutdown();
}



