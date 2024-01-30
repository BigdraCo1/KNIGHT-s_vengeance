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
#include"DrawEntity.h"
enum EYEGUY_ANIMATION_STATES { FLIGTH , FLIGTH_LEFT , ATTACK , ATTACK_LEFT, DEATH , DEATH_LEFT , TAKE_HIT , TAKE_HIT_LEFT
};
class Eyeguy
{

private: 
	int Hp;

	Player* player;
	sf::Sprite sprite;
	sf::IntRect currentFrame;
	std::map<EYEGUY_ANIMATION_STATES, sf::Texture> animationTextures;
	sf::Texture loadTexture(const std::string& filePath);
	bool animationSwitch , Death;
	void initTexture();
	void initVariable(int speed);
	void initSprite();
	void initAnimation();
	int I = 1;
	int CountFrame = 0;
	short animState;
	float ChaseSpeed;
	bool Left;
	bool Damage;
	bool Hit;
	sf::Vector2f dir;
	sf::Clock clock;
	sf::Vector2f SpriteCenter;
	sf::Clock attackTimer;
	sf::Time attackCooldownDuration = sf::seconds(1.0f);
public: 

	Eyeguy(float pos_X, float pos_Y , int speed , Player* player , DrawEntity* Entity);
	virtual ~Eyeguy();
	sf::Clock animationTimer;

	const sf::Sprite getSprite() const;
	const bool& getAnimSwitch() const;
	const bool& getState() const;
	//Accessor
	const sf::FloatRect getGlobalBounds() const;
	const bool& makeDamage();
	void resetAnimationTimer();
	void UpdateMovement(sf::Vector2f playerPositionCenter, sf::Vector2f playerPositionLeft, sf::Vector2f playerPositionRight, bool Chase, bool player_dir);
	void UpdateAnimation();
	void Update(sf::Vector2f playerPositionCenter, sf::Vector2f playerPositionLeft, sf::Vector2f playerPositionRight, bool Chase, bool player_dir);
	void Render(sf::RenderTarget* target);
};

