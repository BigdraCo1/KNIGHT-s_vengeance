#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/System.hpp"
#include"SFML/Network.hpp"
#include"SFML/Window.hpp"
#include"Player.h"
#include"Collision.h"
enum BOSS_ANIMATION_STATES {
	B_IDLE , B_ATTACK_ONE , B_ATTACK_TWO , B_DEATH , B_WARP , B_IDLE_LEFT, B_ATTACK_ONE_LEFT, B_ATTACK_TWO_LEFT, B_DEATH_LEFT, B_WARP_LEFT , TRANSPARENT
};
class Boss
{

private:
	int Hp;
	int Hpmax;
	Player* player;
	sf::Sprite sprite;
	sf::IntRect currentFrame;
	std::map<BOSS_ANIMATION_STATES, sf::Texture> animationTextures;
	sf::Texture loadTexture(const std::string& filePath);
	sf::Sprite empty_bar;
	sf::Sprite Health_bar;
	sf::Texture empty_bar_texture;
	sf::Texture Health_bar_texture;
	bool animationSwitch, Death;
	void initTexture();
	void initVariable();
	void initSprite();
	void initAnimation();
	short animState;
	bool Left;
	bool Over;
	bool Warped;
	bool Near;
	bool Attacked;
	float Shift;
	sf::Vector2f dir;
	sf::Clock clock;
	sf::Vector2f SpriteCenter;
	sf::Clock attackTimer_1;
	sf::Clock attackTimer_2;
	sf::Clock warpTimer;
	sf::Clock HitTimer;
	sf::Time HitDuration = sf::seconds(0.45f);
	sf::Time warpDuration = sf::seconds(1.2f);
	sf::Time attack_1Duration = sf::seconds(0.6f);
	sf::Time attack_2Duration = sf::seconds(0.7f);
public:

	Boss(Player* player);
	virtual ~Boss();
	sf::Clock animationTimer;
	int getHP() const;
	const sf::Sprite getSprite() const;
	const bool& getAnimSwitch() const;
	const bool& getState() const;
	//Accessor
	const sf::FloatRect getGlobalBounds() const;
	const bool& makeDamage();
	void resetAnimationTimer();
	void UpdateMovement();
	void UpdateAnimation();
	void Update();
	void Render(sf::RenderTarget& target);
};


