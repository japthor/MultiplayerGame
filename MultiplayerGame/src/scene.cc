#include "scene.h"
#include "assets.h"
#include "gamemanager.h"
#include "imgui.h"
#include "imgui-sfml.h"
#include "networkmanager.h"
#include <unistd.h>

Scene* Scene::Instance = nullptr;


Scene* Scene::GetInstance()
{
    if (Instance == nullptr)
        Instance = new Scene();
    
    return Instance;
}

Scene::Scene()
{
    CurrentScene = kSceneType_MainMenu;
}

SceneType Scene::GetScene()
{
    return CurrentScene;
}

void Scene::SetScene(SceneType scene)
{
    CurrentScene = scene;
}

sf::Text Scene::GetScoreText()
{
    return ScoreText;
}

sf::Text Scene::GetPoints()
{
    return Points;
}

sf::Text Scene::GetGameOverTitle()
{
    return GameOverTitle;
}

sf::Text Scene::GetGameOverWinText()
{
    return GameOverWinText;
}

sf::Text Scene::GetGameOverWinnerNameText()
{
    return GameOverWinnerNameText;
}

sf::Text Scene::GetGameOverCongratulationsText()
{
    return GameOverCongratulationsText;
}

sf::Text Scene::GetGameOverLoseText()
{
    return GameOverLoseText;
}

sf::Text Scene::GetGameOverLoserNameText()
{
    return GameOverLoserNameText;
}

sf::Text Scene::GetGameOverLoseWinnerText()
{
    return GameOverLoseWinnerText;
}

sf::Text Scene::GetInGameNameText()
{
	return InGameNameText;
}

sf::Text Scene::GetInGameOtherUsersPointsText1()
{
	return InGameOtherUsersPointsText1;
}

sf::Text Scene::GetInGameOtherUsersPointsText2()
{
	return InGameOtherUsersPointsText2;
}

sf::Text Scene::GetInGameOtherUsersPointsText3()
{
	return InGameOtherUsersPointsText3;
}

sf::Text Scene::GetInGameOtherUsersPointsText4()
{
	return InGameOtherUsersPointsText4;
}

std::string Scene::GetGameOverWinName()
{
    return GameOverWinnerName;
}

void Scene::SetGameOverWinnerName(std::string name)
{
    GameOverWinnerName = name;
}

std::string Scene::GetGameOverLoserName()
{
    return GameOverLoserName;
}

void Scene::SetGameOverLoserName(std::string name)
{
    GameOverLoserName = name;
}

void Scene::SetInGameOtherUsersPointsPosXY(User user, float x, float y, int points)
{
	switch (user)
	{
	case kUser_1:
		User1.PosX = x;
		User1.PosY = y;
		User1.Points = points;
		break;
	case kUser_2:
		User2.PosX = x;
		User2.PosY = y;
		User2.Points = points;
		break;
	case kUser_3:
		User3.PosX = x;
		User3.PosY = y;
		User3.Points = points;
		break;
	case kUser_4:
		User4.PosX = x;
		User4.PosY = y;
		User4.Points = points;
		break;
	default:
		break;
	}

}

void Scene::CheckFiles()
{
    if (!Font.loadFromFile(ASSETS::ImagePath("Font.ttf")))
        printf("Font Not Found");
}

void Scene::DrawMainMenu()
{
    GameManager::GetInstance()->RenderIMGUI();
}

void Scene::UpdateMainMenu()
{
    GameManager::GetInstance()->UpdateIMGUI();
    
    ImGui::Begin("Game Window");
    ImGui::Text("Welcome!");
    ImGui::Separator();
    ImGui::NextColumn();
    ImGui::Text("Please, make sure the 'Server' is connected.");
    static bool checkedServerText = false;
    ImGui::Checkbox("<-- Click if it is 'On'", &checkedServerText);
    
    if(checkedServerText){
        ImGui::Separator();
        ImGui::NextColumn();
        ImGui::Text("Server Information:");
        static char buffer[128] = "152.105.5.137";
        ImGui::InputText("IP", buffer, sizeof(buffer));
        
        ImGui::Separator();
        ImGui::NextColumn();
        ImGui::Text("Login Information:");
        static char usernameBuffer[128];
        ImGui::InputText("Username", usernameBuffer, sizeof(usernameBuffer));
        
        static char passwordBuffer[128];
        ImGui::InputText("Password", passwordBuffer, sizeof(passwordBuffer),ImGuiInputTextFlags_Password);
        
        ImGui::Separator();
        ImGui::NextColumn();
        ImGui::Text("Additional information:");
        ImGui::Text("- Server:");
        ImGui::Text("   Remember that the server will automatically close when");
        ImGui::Text("   the game is over.");
        ImGui::Text("- New Account?");
        ImGui::Text("   Just write inside the 'Login Information' section as you");
        ImGui::Text("   you had an account. It will create a new if the username");
        ImGui::Text("   is not used.");
        ImGui::Separator();
        
        static bool checkedAdditionalInformation = false;
        ImGui::Text("Have you read the 'Additional Information' section?");
        ImGui::Checkbox("<-- Click if 'Yes'", &checkedAdditionalInformation);
        
        ImGui::Separator();
        
        static bool status = true;
        if (!status) {
            ImGui::Separator();
            ImGui::Text("Wrong Username or Password");
        }
        
        if(checkedAdditionalInformation){
            ImGui::Text("");
            ImGui::Text("Connect to the Game:");
            if (ImGui::Button("Connect",ImVec2(135,0))) {
                printf("\nConnecting...");
                sleep(2);
                if (NetWorkManager::GetInstance()->Connect(buffer, usernameBuffer, passwordBuffer)) {
                    printf("\nConnected...");
                    checkedAdditionalInformation = false;
                    checkedServerText = false;
                    InGameName = usernameBuffer;
                    CurrentScene = kSceneType_Game;
                }
                else {
                    printf("\nFail to Connect...");
                    status = false;
                }
            }
        }
    }
     
    GameManager::GetInstance()->EndIMGUI();
}

void Scene::DrawGameLabels()
{
    ScoreText.setFont(Font);
    ScoreText.setString("Score:");
    ScoreText.setCharacterSize(40);
    ScoreText.setPosition(500.0f, 50.0f);
    ScoreText.setColor(sf::Color::White);
    
    Points.setFont(Font);
    
    Points.setString(std::to_string(NetWorkManager::GetInstance()->GetPoints()));
    Points.setCharacterSize(40);
    Points.setPosition(650.0f, 50.0f);
    Points.setColor(sf::Color::White);

		InGameNameText.setFont(Font);
		InGameNameText.setOrigin(InGameNameText.getLocalBounds().left +
														 InGameNameText.getLocalBounds().width / 2.0f,
														 InGameNameText.getLocalBounds().top +
														 InGameNameText.getLocalBounds().height / 2.0f);
		InGameNameText.setPosition(800.0f / 2, 20.0f);
		InGameNameText.setString("Playing as: " + InGameName);
		InGameNameText.setCharacterSize(20);
		InGameNameText.setColor(sf::Color::White);

		InGameOtherUsersPointsText1.setFont(Font);
		InGameOtherUsersPointsText1.setOrigin(InGameOtherUsersPointsText1.getLocalBounds().left +
																					InGameOtherUsersPointsText1.getLocalBounds().width / 2.0f,
																					InGameOtherUsersPointsText1.getLocalBounds().top +
																					InGameOtherUsersPointsText1.getLocalBounds().height / 2.0f);
		InGameOtherUsersPointsText1.setPosition(User1.PosX, User1.PosY - 50.0f);
		InGameOtherUsersPointsText1.setString("Score: " + std::to_string(User1.Points));
		InGameOtherUsersPointsText1.setCharacterSize(20);
		InGameOtherUsersPointsText1.setColor(sf::Color::White);

		InGameOtherUsersPointsText2.setFont(Font);
		InGameOtherUsersPointsText2.setOrigin(InGameOtherUsersPointsText2.getLocalBounds().left +
																					InGameOtherUsersPointsText2.getLocalBounds().width / 2.0f,
																					InGameOtherUsersPointsText2.getLocalBounds().top +
																					InGameOtherUsersPointsText2.getLocalBounds().height / 2.0f);
		InGameOtherUsersPointsText2.setPosition(User2.PosX, User2.PosY - 50.0f);
		InGameOtherUsersPointsText2.setString("Score: " + std::to_string(User2.Points));
		InGameOtherUsersPointsText2.setCharacterSize(20);
		InGameOtherUsersPointsText2.setColor(sf::Color::White);

		InGameOtherUsersPointsText3.setFont(Font);
		InGameOtherUsersPointsText3.setOrigin(InGameOtherUsersPointsText3.getLocalBounds().left +
			InGameOtherUsersPointsText3.getLocalBounds().width / 2.0f,
			InGameOtherUsersPointsText3.getLocalBounds().top +
			InGameOtherUsersPointsText3.getLocalBounds().height / 2.0f);
		InGameOtherUsersPointsText3.setPosition(User3.PosX, User3.PosY - 50.0f);
		InGameOtherUsersPointsText3.setString("Score: " + std::to_string(User3.Points));
		InGameOtherUsersPointsText3.setCharacterSize(20);
		InGameOtherUsersPointsText3.setColor(sf::Color::White);

		InGameOtherUsersPointsText4.setFont(Font);
		InGameOtherUsersPointsText4.setOrigin(InGameOtherUsersPointsText4.getLocalBounds().left +
																					InGameOtherUsersPointsText4.getLocalBounds().width / 2.0f,
																					InGameOtherUsersPointsText4.getLocalBounds().top +
																					InGameOtherUsersPointsText4.getLocalBounds().height / 2.0f);
		InGameOtherUsersPointsText4.setPosition(User4.PosX, User4.PosY - 50.0f);
		InGameOtherUsersPointsText4.setString("Score: " + std::to_string(User4.Points));
		InGameOtherUsersPointsText4.setCharacterSize(20);
		InGameOtherUsersPointsText4.setColor(sf::Color::White);
    
}

void Scene::UpdateGameLabels()
{
    
}

void Scene::DrawGameOverWin()
{
    GameManager::GetInstance()->RenderIMGUI();
    
    GameOverTitle.setFont(Font);
    GameOverTitle.setOrigin(GameOverTitle.getLocalBounds().left +
                            GameOverTitle.getLocalBounds().width / 2.0f,
                            GameOverTitle.getLocalBounds().top +
                            GameOverTitle.getLocalBounds().height / 2.0f);
    
    GameOverTitle.setPosition(800 / 2.0f, 100);
    GameOverTitle.setString("Game Over");
    GameOverTitle.setCharacterSize(80);
    GameOverTitle.setColor(sf::Color::White);
    
    GameOverWinText.setFont(Font);
    GameOverWinText.setOrigin(GameOverWinText.getLocalBounds().left +
                              GameOverWinText.getLocalBounds().width / 2.0f,
                              GameOverWinText.getLocalBounds().top +
                              GameOverWinText.getLocalBounds().height / 2.0f);
    
    GameOverWinText.setPosition(800 / 2.0f, 250);
    GameOverWinText.setString("You win!");
    GameOverWinText.setCharacterSize(40);
    GameOverWinText.setColor(sf::Color::White);
    
    GameOverWinnerNameText.setFont(Font);
    GameOverWinnerNameText.setOrigin(GameOverWinnerNameText.getLocalBounds().left +
                                     GameOverWinnerNameText.getLocalBounds().width / 2.0f,
                                     GameOverWinnerNameText.getLocalBounds().top +
                                     GameOverWinnerNameText.getLocalBounds().height / 2.0f);
    GameOverWinnerNameText.setPosition(800 / 2.0f, 600 / 2.0f);
    GameOverWinnerNameText.setString(GameOverWinnerName);
    GameOverWinnerNameText.setCharacterSize(30);
    GameOverWinnerNameText.setColor(sf::Color::White);
    
    GameOverCongratulationsText.setFont(Font);
    GameOverCongratulationsText.setOrigin(GameOverCongratulationsText.getLocalBounds().left +
                                          GameOverCongratulationsText.getLocalBounds().width / 2.0f,
                                          GameOverCongratulationsText.getLocalBounds().top +
                                          GameOverCongratulationsText.getLocalBounds().height / 2.0f);
    GameOverCongratulationsText.setPosition(800 / 2.0f, 360.0f);
    GameOverCongratulationsText.setString("Congratulations!");
    GameOverCongratulationsText.setCharacterSize(40);
    GameOverCongratulationsText.setColor(sf::Color::White);
}

void Scene::DrawGameOverLose()
{
    
    GameOverTitle.setFont(Font);
    GameOverTitle.setOrigin(GameOverTitle.getLocalBounds().left +
                            GameOverTitle.getLocalBounds().width / 2.0f,
                            GameOverTitle.getLocalBounds().top +
                            GameOverTitle.getLocalBounds().height / 2.0f);
    
    GameOverTitle.setPosition(800 / 2.0f, 100);
    GameOverTitle.setString("Game Over");
    GameOverTitle.setCharacterSize(80);
    GameOverTitle.setColor(sf::Color::White);
    
    GameOverLoseText.setFont(Font);
    GameOverLoseText.setOrigin(GameOverLoseText.getLocalBounds().left +
                               GameOverLoseText.getLocalBounds().width / 2.0f,
                               GameOverLoseText.getLocalBounds().top +
                               GameOverLoseText.getLocalBounds().height / 2.0f);
    
    GameOverLoseText.setPosition(800 / 2.0f, 250);
    GameOverLoseText.setString("You lose!");
    GameOverLoseText.setCharacterSize(40);
    GameOverLoseText.setColor(sf::Color::White);
    
    GameOverLoserNameText.setFont(Font);
    GameOverLoserNameText.setOrigin(GameOverLoserNameText.getLocalBounds().left +
                                    GameOverLoserNameText.getLocalBounds().width / 2.0f,
                                    GameOverLoserNameText.getLocalBounds().top +
                                    GameOverLoserNameText.getLocalBounds().height / 2.0f);
    GameOverLoserNameText.setPosition(800 / 2.0f, 600 / 2.0f);
    GameOverLoserNameText.setString(GameOverLoserName);
    GameOverLoserNameText.setCharacterSize(30);
    GameOverLoserNameText.setColor(sf::Color::White);
    
    GameOverLoseWinnerText.setFont(Font);
    GameOverLoseWinnerText.setOrigin(GameOverLoseWinnerText.getLocalBounds().left +
                                     GameOverLoseWinnerText.getLocalBounds().width / 2.0f,
                                     GameOverLoseWinnerText.getLocalBounds().top +
                                     GameOverLoseWinnerText.getLocalBounds().height / 2.0f);
    GameOverLoseWinnerText.setPosition(800 / 2.0f, 360.0f);
    GameOverLoseWinnerText.setString(GameOverWinnerName + " wins!");
    GameOverLoseWinnerText.setCharacterSize(40);
    GameOverLoseWinnerText.setColor(sf::Color::White);
    
    GameManager::GetInstance()->RenderIMGUI();
    
}

void Scene::UpdateGameOver()
{
    GameManager::GetInstance()->UpdateIMGUI();
    ImGui::Begin("Game Window");
    
    if (ImGui::Button("Go to Menu", ImVec2(135, 0))) {
        NetWorkManager::GetInstance()->Disconnect();
        GameManager::GetInstance()->Reset();
        CurrentScene = kSceneType_MainMenu;
    }
    
    
    GameManager::GetInstance()->EndIMGUI();
}

void Scene::InputScene(SceneType scene)
{
    switch (scene)
    {
        case kSceneType_MainMenu:
            InputMainMenu();
            break;
        case kSceneType_Game:
            
        default:
            break;
    }
    
}

void Scene::Update(SceneType scene)
{
    switch (scene)
    {
        case kSceneType_MainMenu:
            UpdateMainMenu();
            break;
        case kSceneType_Game:
            
            break;
        case kSceneType_GameOverWin:
            UpdateGameOver();
            break;
        case kSceneType_GameOverLose:
            UpdateGameOver();
            break;
            
        default:
            break;
    }
}

void Scene::DrawScene(SceneType scene)
{
    switch (scene)
    {
        case kSceneType_MainMenu:
            DrawMainMenu();
            break;
        case kSceneType_Game:
            DrawGameLabels();
            break;
        case kSceneType_GameOverWin:
            DrawGameOverWin();
            break;
        case kSceneType_GameOverLose:
            DrawGameOverLose();
            break;
        default:
            break;
    }
}        
