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
#include"Tilemap.h"
class DrawEntity
{
private:

	Tilemap tilemaps[12];
	
	void initVariable();
	void initTilemap();
	sf::RenderWindow& window;

public:

	DrawEntity(sf::RenderWindow& window);

	virtual ~DrawEntity();
	int Level[11][12000];
	int Level_U;
	int width;
	int height;
	int tileSize;

	void render();
};

