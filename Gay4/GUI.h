#pragma once
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<time.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> 

#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Network.hpp"
class GUI
{
private:

    sf::Vector2f PoS[6];
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundImage[3]; // Texture for the background image
    sf::Sprite backgroundSprite[3]; // Sprite for the background image
    sf::Texture ArrowImage;
    sf::Sprite ArrowSprite;
    void initGUIElements();
    std::vector<std::pair<std::string, int>> scores;
    std::vector<sf::Text> top3ScoreTexts;
public:
    GUI(sf::RenderWindow& window);
    int index;
    bool isHelp = false;
    bool isAbout = false;
    bool isMenu = true;
    bool isStart = false;
    void handleEvent(sf::Event event);
    void draw();

};