#pragma once
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<time.h>

#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Network.hpp"
#include"Player.h"
#include"GUI.h"
#include"DrawEntity.h"
#include"Coin.h"
#include"Collision.h"
#include"Eyeguy.h"
#include"Boss.h"
enum GameState {
	MENU,
	GAMEPLAY,
	GAMEOVER,
	VICTORY,
	SAVE_GAME,
};
class Game
{
private:
	sf::RenderWindow *window;
	sf::Event ev;
	DrawEntity* drawEntity;
	Player* player;
	Boss* boss;
	GUI* gui;

	sf::Sprite coinIcon;
	sf::Texture coinTexture;

	sf::Font font;
	sf::Text InGameText;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Coin*> coins;
	std::vector<Eyeguy*> eyeguys;
	std::set<int> uniqueNumbers;
	void initWindow();
	void initPlayer();
	void initText();
	void initCoin();
	void initEyeguy();
	void initBoss();
	void initGameOver();
	void initVictory();
	sf::Clock inputTimer;
	bool inputDelayActive = false;
	const sf::Time InputDelay = sf::milliseconds(200);

	sf::Sprite GO[2];
	sf::Texture GO_t[2];
	sf::Text GO_text;

	sf::Sprite Vic;
	sf::Texture Vic_T;
	sf::Text GV_text;
	std::string inputText;
	sf::Text SAVE_text;

	sf::Text Name_text;
	sf::Text nameInput;
	sf::Vector2f Quad[11];
	sf::Vector2u Grid[11];
	sf::View initialView;
	int G_Array[11];
	bool gameDelay = false;
	bool Head;
	bool Hit_[15];
	bool Damage = false;
	bool gameStarted = false;
	bool Restart = false;
	unsigned int coinCount;
	unsigned int score;
	sf::Clock frameClock;
	sf::Clock DelayTimer;
	sf::Clock gameClock;
	float elapsedTime;
	sf::Time DelayDuration = sf::seconds(2.f);
	float deltaTime;
	GameState currentState; // Current game state

	std::vector<std::pair<std::string, int>> scores;
	std::vector<sf::Text> top3ScoreTexts;
	std::vector<sf::Text> topScoreTexts;

	sf::FloatRect textBounds;
	float centerX;
	float centerY;

public:
	//Functions
	Game();
	virtual ~Game();

	//Functions
	sf::View view;
	void updatePlayer();
	void updateCoin();
	void updateEyeguy();
	void updateBoss();
	void updateCollision();
	void updateText();
	void update();
	void renderGUI();
	void renderEntity();
	void renderCoin();
	void renderEyeguy();
	void renderPlayer();
	void renderBoss();
	void renderText();
	void renderGO();
	void renderSaveGame();
	void renderVIC();
	void render();
	const sf::RenderWindow& getWindow() const;
};

