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

class Tilemap : public sf::Drawable, public sf::Transformable
{
private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::VertexArray m_vertices;
		sf::Texture m_tileset;
public:
		bool loadFromResource(const std::string& resourcePath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};


