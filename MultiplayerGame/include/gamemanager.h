#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "object.h"
#include "scene.h"


class GameManager {
public:
	~GameManager() {};
	/// Get World.
	inline b2World* GetWorld() { return World; };
	/// Get Window.
	inline sf::RenderWindow* GetWindow() {return Window;}
	/// Get Input
	inline void GetInput() { return; }
	/// Get the instance 
	static GameManager* GetInstance();
	/// Init
	void Init();
	/// Input
	void Input();
	/// Update
	void Update();
	/// Render
	void Render();

	/**
	* Creates an object
	* @param position Position x and y.
	* @param scale Width and height.
	* @param type Static or dinamic object.
	* @param density Density of the object.
	* @param friction Friction of the object.
	* @param texture Name of the image.
	* @param spriteOrigin Width/2 and height/2.
	* @param SpawnType Type of object.
	* @return An object
	*/
	Object* CreateObject(Vec2 position,Vec2 scale,BodyType type,float32 density,
		                float32 friction,char* texture,Vec2 spriteOrigin,
					          DefineType SpawnType);

	/// Reset the game.
	void Reset();
	/// Init Imgui.
	void InitIMGUI();
	/// Update Imgui.
	void UpdateIMGUI();
	/// Render Imgui.
	void RenderIMGUI();
	/// Render Imgui.
	void EndIMGUI();
	/// Close Imgui.
	void ShutDownIMGUI();
	/// Clock
	sf::Clock deltaClock;

private:
	GameManager() {};
	/// Instance variable
	static GameManager* Instance;
	/// Window variable
	sf::RenderWindow* Window;
	/// World variable
	b2World* World;
	/// Contains all the objects created
	std::vector<Object*> Objects;
};

#endif //__GAMEMANAGER_H__

