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

class Coin
{
private:
	sf::Texture *textures;
	sf::Sprite sprite;
	sf::IntRect currentFrame;
	bool animationSwitch;
	void initVariable();
	void initSprite();
	void initAnimation();

public:
	Coin(sf::Texture* texture, float pos_X, float pos_Y);
	virtual ~Coin();
	sf::Clock animationTimer;

	const sf::Sprite getSprite() const;
	const bool& getAnimSwitch() const;
	//Accessor
	const sf::FloatRect getGlobalBounds() const;

	void resetAnimationTimer();

	

	void Update();
	void Render(sf::RenderTarget* target);
};

