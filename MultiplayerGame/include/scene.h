#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Graphics.hpp>

/**
 * Struct
 * Where to put the text and the number of points on each player
 */
struct PointsPosUsersText {
	float PosX;
	float PosY;
	int Points;
};

/**
 * Enum
 * Differentiate users
 */
enum User {
	kUser_1,
	kUser_2,
	kUser_3,
	kUser_4,
};

/**
 * Enum
 * Types of scenes
 */

enum SceneType
{
	kSceneType_MainMenu,
	kSceneType_Game,
	kSceneType_GameOverWin,
	kSceneType_GameOverLose,
};

class Scene
{
public:
    /// Desstructor
	~Scene() {};
    /// Get instance
	static Scene* GetInstance();
    /// Get scene
	SceneType GetScene();
    /// Set scene
	void SetScene(SceneType scene);
	/// Get score text
	sf::Text GetScoreText();
    /// Get points text
	sf::Text GetPoints();
    /// Get game over title text
	sf::Text GetGameOverTitle();
    /// Get game over win text
	sf::Text GetGameOverWinText();
    /// Get game over winner name text
	sf::Text GetGameOverWinnerNameText();
    /// Get game over congratulations text
	sf::Text GetGameOverCongratulationsText();
    /// Get game over lose text
	sf::Text GetGameOverLoseText();
    /// Get game over loser name text
	sf::Text GetGameOverLoserNameText();
    /// Get game over loser winner text
	sf::Text GetGameOverLoseWinnerText();
	/// Get in game name text
	sf::Text GetInGameNameText();
	/// Get in game other users points text;
	sf::Text GetInGameOtherUsersPointsText1();
	/// Get in game other users points 2 text;
	sf::Text GetInGameOtherUsersPointsText2();
	/// Get in game other users points 3 text;
	sf::Text GetInGameOtherUsersPointsText3();
	/// Get in game other users points 4 text;
	sf::Text GetInGameOtherUsersPointsText4();
    /// Get game over win name
	std::string GetGameOverWinName();
    /// Set game over winner name
	void SetGameOverWinnerName(std::string name);
    /// Get game over loser name
	std::string GetGameOverLoserName();
    /// Set game over loser name
	void SetGameOverLoserName(std::string name);
	/// Set in game other users points pos x, y and points
	void SetInGameOtherUsersPointsPosXY(User user, float x, float y, int points);

    /// Check if files are running
	void CheckFiles();
    /// Draw Main Menu
	void DrawMainMenu();
    /// Input Main Menu
	void InputMainMenu() {};
    /// Update Main Menu
	void UpdateMainMenu();
    /// Draw game labels
	void DrawGameLabels();
    /// Update Game labels
	void UpdateGameLabels();
    /// Draw Game Over Win
	void DrawGameOverWin();
    /// Draw Game Over Lose
	void DrawGameOverLose();
    /// Update Game Over
	void UpdateGameOver();
    /// Input
	void InputScene(SceneType scene);
    /// Update
	void Update(SceneType scene);
    /// Render
	void DrawScene(SceneType scene);

private:
    /// Constructor
	Scene();
    /// Instance
	static Scene* Instance;
    /// Current Scene
	SceneType CurrentScene;
    /// Font
	sf::Font Font;
    /// Score text
	sf::Text ScoreText;
    /// Points text
	sf::Text Points;
	/// GameOver title text
	sf::Text GameOverTitle;
    /// GameOver winner name
	std::string GameOverWinnerName;
    /// GameOver loser name
	std::string GameOverLoserName;
    /// GameOver win text
	sf::Text GameOverWinText;
    /// GameOver winner name text
	sf::Text GameOverWinnerNameText;
    /// GameOver congratulations text
	sf::Text GameOverCongratulationsText;
    /// GameOver lose text
	sf::Text GameOverLoseText;
    /// GameOver loser name text
	sf::Text GameOverLoserNameText;
    /// GameOver lose winner text
	sf::Text GameOverLoseWinnerText;
	/// In Game Name Text
	sf::Text InGameNameText;
	/// User Name
	std::string InGameName;
	/// In Game Other Users Points Text 1
	sf::Text InGameOtherUsersPointsText1;
	/// In Game Other Users Points Text 2
	sf::Text InGameOtherUsersPointsText2;
	/// In Game Other Users Points Text 3
	sf::Text InGameOtherUsersPointsText3;
	/// In Game Other Users Points Text 4
	sf::Text InGameOtherUsersPointsText4;
	/// Pos x and y of user 1 points text
	PointsPosUsersText User1;
	/// Pos x and y of user 2 points text
	PointsPosUsersText User2;
	/// Pos x and y of user 3 points text
	PointsPosUsersText User3;
	/// Pos x and y of user 4 points text
	PointsPosUsersText User4;

};

#endif //__GAMEMANAGER_H__
