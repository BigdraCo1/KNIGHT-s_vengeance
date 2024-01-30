#include "GUI.h"



void GUI::initGUIElements()
{
    index = 0;
    this->PoS[0] = sf::Vector2f(140, 180);
    this->PoS[1] = sf::Vector2f(140, 295);
    this->PoS[2] = sf::Vector2f(140, 405);
    this->PoS[3] = sf::Vector2f(140, 515);
    
    if (!backgroundImage[0].loadFromFile("./GUI/GOLDEN HOUR.png")) {
        std::cerr << "Failed to load background image." << std::endl;
    }
    if (!backgroundImage[1].loadFromFile("./GUI/2.png")) {
        std::cerr << "Failed to load background image." << std::endl;
    }
    if (!backgroundImage[2].loadFromFile("./GUI/3.png")) {
        std::cerr << "Failed to load background image." << std::endl;
    }

    backgroundSprite[0].setTexture(this->backgroundImage[0]);
    backgroundSprite[1].setTexture(this->backgroundImage[1]);
    backgroundSprite[2].setTexture(this->backgroundImage[2]);
    backgroundSprite[0].setPosition(0, 0);
    backgroundSprite[1].setPosition(0, 0);
    backgroundSprite[2].setPosition(0, 0);

    if (!ArrowImage.loadFromFile("./GUI/ARROW0.png")) {
        // Handle the case where the image fails to load
        std::cerr << "Failed to load background image." << std::endl;
    }
    ArrowSprite.setTexture(ArrowImage);
    ArrowSprite.setScale(0.1f, 0.1f); 
    ArrowSprite.setPosition(this->PoS[0]);
}

GUI::GUI(sf::RenderWindow& window) : window(window) {
    initGUIElements();
}                                                                                                                                                                                                                                                                                                                                                                                                                                                               

void GUI::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed && isMenu) {
        if (event.key.code == sf::Keyboard::Enter && index == 0 ) {
            this->isStart = true;
            this->isAbout = false;
            this->isHelp = false;
            this->isMenu = false;
        }
        else if (event.key.code == sf::Keyboard::S && index < 3 ) {
            index++;
        }
        else if (event.key.code == sf::Keyboard::W && index > 0 ) {
            index--;
        }
        else if (event.key.code == sf::Keyboard::Enter && index == 1)
        {
            this->isStart = false;
            this->isAbout = false;
            this->isHelp = true;
            this->isMenu = false;
        }
        else if (event.key.code == sf::Keyboard::Enter && index == 2 )
        {
            this->isStart = false;
            this->isAbout = true;
            this->isHelp = false;
            this->isMenu = false;
        }
        else if (event.key.code == sf::Keyboard::Enter && index == 3 )
        {
            window.close();
        }
        ArrowSprite.setPosition(this->PoS[index]);
    }

    if (isHelp)
    {
        if (event.key.code == sf::Keyboard::BackSpace)
        {
            this->isStart = false;
            this->isAbout = false;
            this->isHelp = false;
            this->isMenu = true;
        }
    }
    else if (isAbout)
    {
        if (event.key.code == sf::Keyboard::BackSpace)
        {
            this->isStart = false;
            this->isAbout = false;
            this->isHelp = false;
            this->isMenu = true;
        }
    }

}


void GUI::draw()
{
    if (isMenu)
    {
        window.draw(backgroundSprite[0]);
        window.draw(ArrowSprite);
    }
    else if (isHelp)
    {
        window.draw(backgroundSprite[1]);
    }
    else if (isAbout)
    {
        window.draw(backgroundSprite[2]);
    }
}
