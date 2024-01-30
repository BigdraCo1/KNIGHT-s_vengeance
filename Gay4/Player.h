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
enum PLAYER_ANIMATION_STATES {IDLE			 = 0	,IDLE_LEFT				= 1,
							  MOVING_LEFT	 = 2	,MOVING_RIGHT			= 3  , 
							  JUMPING		 = 4	,JUMPING_LEFT			= 5  , 
						      FALLING		 = 6	,FALLING_LEFT			= 7  ,
							  CROUCH_WALK	 = 8	,CROUCH_WALK_LEFT		= 9  , 
							  CROUCH		 = 10	,CROUCH_LEFT			= 11 , 
							  STATSIMPATTACK = 12	,STATSIMPLEATTACK_LEFT  = 13 , 
							  ROLLING		 = 14	,ROLLING_LEFT			= 15 ,
							  P_DEATH		 = 16   ,P_DEATH_LEFT			= 17};
class Player
{
private:
	sf::Sprite sprite;
	sf::Sprite RnB; sf::Texture RnBTexture;
	sf::Sprite Red; sf::Texture RedTexture;
	sf::Sprite Blue; sf::Texture BlueTexture;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Texture loadTexture(const std::string& filePath);
	
	int Hp;
	int Hpmax;
	float Sp;
	int Spmax;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	std::map<PLAYER_ANIMATION_STATES, sf::Texture> animationTextures;
	bool animationSwitch;
	float Shift;
	sf::Clock attackTimer , JumpTimer , RegenTimer;
	bool isAttacking, Moving, Crouching, Jumping, Rolling;
	sf::Time attackDuration = sf::seconds(0.45f);
	sf::Time attackCooldownDuration = sf::seconds(0.7f);
	sf::Time JumpDuratiion = sf::seconds(0.5f);
	
	//Core
	void initVariables();
	void initHealthbar();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();


public:
	Player();
	virtual ~Player();

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	bool RollingStatus;
	bool left;
	//Accessors
	int getHP() const;
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	short getAnimstate() const;
	float getVelocityX() const;
	const bool& getDir();
	const sf::IntRect getCurrentFrame() const;
	const sf::Sprite getSprite() const;
	//Modifiers
	


	void takeDamage(const int damage);
	void useStaminapoint(const int usSp);
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void resetVelocityX();
	void RecieverRolling(bool Collision);

	//F(x)
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimation();
	void updateHealthbar();
	void update();
	void render(sf::RenderTarget& target);
};

