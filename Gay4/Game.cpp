#include "Game.h"
#include <iostream>
#include <random>

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 630), "KNIGHT's vengeance", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->DelayTimer.restart();
}

void Game::initPlayer()
{
    this->player = new Player();
    this->Head = false;
}

void Game::initText()
{
    if (!this->font.loadFromFile("./Font/MorrisRomanAlternate-Black.ttf"))
    {
        std::cout << "ERROR" << "\n";
    }
    this->InGameText.setFont(this->font);
    this->InGameText.setCharacterSize(45);
    this->InGameText.setFillColor(sf::Color::White);
    this->InGameText.setString("NONE");

    this->SAVE_text.setFont(this->font);
    this->SAVE_text.setCharacterSize(75);
    this->SAVE_text.setFillColor(sf::Color::White);
    this->SAVE_text.setString("NONE");

    this->Name_text.setFont(this->font);
    this->Name_text.setCharacterSize(75);
    this->Name_text.setFillColor(sf::Color::White);
    this->Name_text.setPosition(350, 400);
    this->Name_text.setString("YOUR NAME : " );
}

void Game::initCoin()
{
    this->deltaTime = 0.0f;
    this->textures["COIN"] = new sf::Texture();
    this->textures["COIN"]->loadFromFile("./Entity/Coin.png");
    if (!this->coinTexture.loadFromFile("./Entity/Coin101.png"))
    {
        std::cout << "ERROR: Texture not found at path: " << "./Entity/Coin101.png" << "\n";
    }
    this->coinCount = 0;
    this->coinIcon.setTexture(this->coinTexture);
    this->coinIcon.setScale(4.f, 4.f);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    

    std::set<int> uniqueNumbers;

    while (uniqueNumbers.size() < 200) {
        int random_number = std::rand() % 12000;
        if ((random_number >= 7260 && random_number <= 7265) || (random_number >= 3833 - 600 && random_number <= 3845 - 600) || (random_number >= 3833 && random_number <= 3845) || (random_number >= 7884 - 2400 && random_number <= 7889 - 2400) || (random_number >= 7884 - 1800 && random_number <= 7889 - 1800) || (random_number >= 7884 - 1200 && random_number <= 7889 - 1200) || (random_number >= 7884 - 600 && random_number <= 7889 - 600) || (random_number >= 7884 && random_number <= 7889) || (random_number >= 5928 && random_number <= 5939) || random_number == 6218 || random_number == 3839 || random_number == 3252 || random_number == 2047 || random_number == 6219 || random_number == 5014 || (random_number >= 5020 && random_number <= 5032) || (random_number >= 7415 && random_number <= 7417) || (random_number >= 10475 - 600 && random_number <= 10696 - 600) || (random_number >= 10475 && random_number <= 10696) || (random_number >= 8645 && random_number <= 8665) || (random_number >= 10312 && random_number <= 10400) || (random_number >= 5466 && random_number <= 5483) || (random_number >= 7899 && random_number <= 7905) || (random_number >= 2498 && random_number <= 2508) || (random_number == 9205) || (random_number == 7408))
        {
            uniqueNumbers.insert(random_number - 600);
        }
    }

    for (int number : uniqueNumbers) {
        this->coins.push_back(new Coin(this->textures["COIN"], static_cast<int>(32 * (number % (300 * 2))), static_cast<int>(32 * (number / (300 * 2)))));
    }
}

void Game::initEyeguy()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> yDistribution(0, 400);
    std::uniform_int_distribution<int> xDistribution(3590, 6430); 
    std::uniform_int_distribution<int> sDistribution(10, 40);

    for (size_t i = 0; i < 30; i++)
    {
        int randomY = yDistribution(generator);
        int randomX = xDistribution(generator);
        int randomS = sDistribution(generator);
        this->eyeguys.push_back(new Eyeguy(randomX, randomY , randomS , player , drawEntity));
        std::cout << randomX << " , " << randomY << std::endl;
    }
}

void Game::initBoss()
{
    this->boss = new Boss(player);
}

void Game::initGameOver()
{  
    if (!this->GO_t[0].loadFromFile("./GUI/shirt-1625555745-edb14e2fb2f377c66df4bcb08224980d-removebg.png"))
    {
        std::cout << "ERROR" << "\n";
    }
    this->GO[0].setTexture(this->GO_t[0]);
    // Get the size of the window
    sf::Vector2u windowSize = this->window->getSize();

    // Get the size of the sprite
    sf::Vector2f spriteSize = this->GO[0].getLocalBounds().getSize();

    // Calculate the position to center the sprite
    sf::Vector2f position;
    position.x = (windowSize.x - 600) / 2.0f;
    position.y = (windowSize.y - 600) / 2.0f;

    // Set the sprite's position to the calculated position
    this->GO[0].setPosition(position.x , position.y - 30);
    this->GO[0].setScale(600.f / 800.f, 600.f / 800.f);

    this->GO_text.setFont(this->font);
    this->GO_text.setCharacterSize(45);
    this->GO_text.setPosition(position.x + 100, position.y + 540);
    this->GO_text.setFillColor(sf::Color::White);
    this->GO_text.setString("NONE");
}

void Game::initVictory()
{
    if (!this->Vic_T.loadFromFile("./GUI/pixel-art-8-bit-you-win-text-winner-golden-cups-vector-33826578.jpg"))
    {
        std::cout << "ERROR" << "\n";
    }
    sf::Vector2u windowSize = this->window->getSize();

    // Get the size of the sprite
    sf::Vector2f spriteSize = this->Vic.getLocalBounds().getSize();

    // Calculate the position to center the sprite
    sf::Vector2f position;
    position.x = (windowSize.x - 604) / 2.0f;
    position.y = (windowSize.y - 394) / 2.0f;
    this->Vic.setTexture(this->Vic_T);
    this->Vic.setPosition(position);
    this->GV_text.setFont(this->font);
    this->GV_text.setCharacterSize(45);
    this->GV_text.setPosition(510, 530);
    this->GV_text.setFillColor(sf::Color::White);
    this->GV_text.setString("NONE");
}



Game::Game() : player(nullptr), gui(nullptr), drawEntity(nullptr)
{
    // Initialize the game window and player
    this->initWindow();
    this->initGameOver();
    this->initVictory();
    this->initPlayer();
    this->initText();
    this->initCoin();
    this->initEyeguy();
    this->initBoss();
    this->elapsedTime = 0;
    view = this->window->getDefaultView();
    this->initialView = window->getView();

    gui = new GUI(*window);
    drawEntity = new DrawEntity(*window);

    
}

Game::~Game()
{
    delete this->player;
    delete this->boss;
    delete this->gui;
    delete this->drawEntity;
    delete this->window;
  
    for (auto& i : this->textures)
    {
        delete i.second;
    }
   
    for (auto* i : this->coins)
    {
        delete i;
    }

    for (auto* i : this->eyeguys)
    {
        delete i;
    }
}

void Game::updatePlayer()
{
    this->player->update();
}

void Game::updateCoin()
{
    for (size_t i = 0; i < this->coins.size() ; i++)
    {
        bool Coins_remove = false;
        if (this->coins[i]->getGlobalBounds().intersects(this->player->getGlobalBounds()))
        {
            if (Collision::pixelPerfectTest(this->coins[i]->getSprite(), this->player->getSprite()))
            {
                delete this->coins[i];
                this->coins[i] = nullptr;
                Coins_remove = true;
            }
        }

        if (Coins_remove)
        {
            this->coins.erase(std::remove(this->coins.begin(), this->coins.end(), nullptr), this->coins.end());
            coinCount++;
        }
    }
    
    for (auto* coin : this->coins) {
        coin->Update();
    }
    sf::View currentView = window->getView();
    coinIcon.setPosition(currentView.getCenter().x + 10.f - currentView.getSize().x / 2, currentView.getCenter().y + 10.f - currentView.getSize().y / 2);
}

void Game::updateEyeguy()
{
    bool Chase = false; 
    for (size_t i = 0; i < this->eyeguys.size(); i++)
    {
        if (drawEntity->Level[6][this->G_Array[10]] != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
        {
            Chase = false;
        }
        else if (this->player->getPosition().x >= 3500 && ((this->eyeguys[i]->getGlobalBounds().left -  this->player->getPosition().x <= 315) && ( this->player->getPosition().x - this->eyeguys[i]->getGlobalBounds().left >= -315)))
        {
            Chase = true;
        }

        if (this->eyeguys[i]->getState())
        {
            delete this->eyeguys[i];
            this->eyeguys[i] = nullptr;
            this->eyeguys.erase(std::remove(this->eyeguys.begin(), this->eyeguys.end(), nullptr), this->eyeguys.end());
        }
    }
    sf::Vector2f playerPositionCenter = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 2, this->player->getPosition().y + 3 * this->player->getGlobalBounds().height / 4);
    sf::Vector2f playerPositionLeft = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 4, this->player->getPosition().y + 3 * this->player->getGlobalBounds().height / 4);
    sf::Vector2f playerPositionRight = sf::Vector2f(this->player->getPosition().x + 3 * this->player->getGlobalBounds().width / 4, this->player->getPosition().y + 3 * this->player->getGlobalBounds().height / 4);
    for (auto* eyeguy : this->eyeguys) {
        eyeguy->Update(playerPositionCenter, playerPositionLeft , playerPositionRight, Chase , this->player->getDir() );
    }
}

void Game::updateBoss()
{
    this->boss->Update();
}


void Game::updateCollision()
{

    this->Quad[0] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 8, this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
    this->Quad[1] = sf::Vector2f(this->player->getPosition().x + 3 * this->player->getGlobalBounds().width / 8, this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
    this->Quad[2] = sf::Vector2f(this->player->getPosition().x + 3 * this->player->getGlobalBounds().width / 8 + this->player->getGlobalBounds().width / 4, this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
    this->Quad[3] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 8 + 3 * this->player->getGlobalBounds().width / 4, this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
    this->Quad[4] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 8, this->player->getPosition().y + this->player->getGlobalBounds().height );
    this->Quad[5] = sf::Vector2f(this->player->getPosition().x + 3 * this->player->getGlobalBounds().width / 8, this->player->getPosition().y + this->player->getGlobalBounds().height );
    this->Quad[6] = sf::Vector2f(this->player->getPosition().x + 3 * this->player->getGlobalBounds().width / 8 + this->player->getGlobalBounds().width / 4, this->player->getPosition().y + this->player->getGlobalBounds().height );
    this->Quad[7] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 8 + 3 * this->player->getGlobalBounds().width / 4, this->player->getPosition().y + this->player->getGlobalBounds().height );
    this->Quad[8] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 2 , this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
    this->Quad[9] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 2, this->player->getPosition().y + this->player->getGlobalBounds().height );
    this->Quad[10] = sf::Vector2f(this->player->getPosition().x + this->player->getGlobalBounds().width / 2, this->player->getPosition().y + 3 * this->player->getGlobalBounds().height / 4);
   //Red    Quad[0] , Quad[3] , Quad[4] , Quad[7]
   //Green  Quad[1] , Quad[2] , Quad[5] , Quad[6]
   //Center Quad[8] , Quad[9]
    for (size_t i = 0; i < 11; i++)
    {
        this->Grid[i].x = static_cast<int>(this->Quad[i].x / drawEntity->tileSize);
        this->Grid[i].y = static_cast<int>(this->Quad[i].y / drawEntity->tileSize);
        this->G_Array[i] = this->Grid[i].x + drawEntity->width * 2 * this->Grid[i].y;
    }
    
    
    
    if (this->player->getPosition().x + 3 * this->player->getGlobalBounds().width / 4 <  0 + this->player->getGlobalBounds().width / 4)
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            - this->player->getGlobalBounds().width /2 ,
            this->player->getGlobalBounds().top
        );
    }
    if (this->player->getPosition().x - 3 * this->player->getGlobalBounds().width / 4 > 19200 + this->player->getGlobalBounds().width / 8 )
    {
        this->currentState = GAMEOVER;
    }
    if (this->player->getPosition().y  > 1000)
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getPosition().x,
            900
        );
    }
    
    //Level0

    //Horizontal
    if ((drawEntity->Level[8][this->G_Array[8]] == 106 || drawEntity->Level[0][this->G_Array[9]] == 106 || drawEntity->Level[0][this->G_Array[10]] == 106) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
         this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top
            
        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 100 || drawEntity->Level[0][this->G_Array[9]] == 100 || drawEntity->Level[0][this->G_Array[10]] == 100) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 102 || drawEntity->Level[0][this->G_Array[9]] == 102 || drawEntity->Level[0][this->G_Array[10]] == 102) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 116 || drawEntity->Level[0][this->G_Array[9]] == 116 || drawEntity->Level[0][this->G_Array[10]] == 116) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 16 || drawEntity->Level[0][this->G_Array[9]] == 16 || drawEntity->Level[0][this->G_Array[10]] == 16) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 32 || drawEntity->Level[0][this->G_Array[9]] == 32 || drawEntity->Level[0][this->G_Array[10]] == 32) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 118 || drawEntity->Level[0][this->G_Array[9]] == 118 || drawEntity->Level[0][this->G_Array[10]] == 118) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 122 || drawEntity->Level[0][this->G_Array[9]] == 122 || drawEntity->Level[0][this->G_Array[10]] == 122) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    //Left
    else if ((drawEntity->Level[8][this->G_Array[8]] == 239 || drawEntity->Level[0][this->G_Array[9]] == 239 || drawEntity->Level[0][this->G_Array[10]] == 239) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 255 || drawEntity->Level[0][this->G_Array[9]] == 255 || drawEntity->Level[0][this->G_Array[10]] == 255) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 116 || drawEntity->Level[0][this->G_Array[9]] == 116 || drawEntity->Level[0][this->G_Array[10]] == 116) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 100 || drawEntity->Level[0][this->G_Array[9]] == 100 || drawEntity->Level[0][this->G_Array[10]] == 100) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 18 || drawEntity->Level[0][this->G_Array[9]] == 18 || drawEntity->Level[0][this->G_Array[10]] == 18) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 34 || drawEntity->Level[0][this->G_Array[9]] == 34 || drawEntity->Level[0][this->G_Array[10]] == 34) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 239 || drawEntity->Level[0][this->G_Array[9]] == 239 || drawEntity->Level[0][this->G_Array[10]] == 239) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 255 || drawEntity->Level[0][this->G_Array[9]] == 255 || drawEntity->Level[0][this->G_Array[10]] == 255) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 116 || drawEntity->Level[0][this->G_Array[9]] == 116 || drawEntity->Level[0][this->G_Array[10]] == 116) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 100 || drawEntity->Level[0][this->G_Array[9]] == 100 || drawEntity->Level[0][this->G_Array[10]] == 100) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 18 || drawEntity->Level[0][this->G_Array[9]] == 18 || drawEntity->Level[0][this->G_Array[10]] == 18) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else if ((drawEntity->Level[8][this->G_Array[8]] == 34 || drawEntity->Level[0][this->G_Array[9]] == 34 || drawEntity->Level[0][this->G_Array[10]] == 34) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityX();
        this->player->setPosition(

            this->Grid[0].x * this->drawEntity->tileSize - this->player->getGlobalBounds().width / 16,
            this->player->getGlobalBounds().top

        );
        this->player->RecieverRolling(false);
    }
    else
    {
        this->player->RecieverRolling(true);
       
        
    }
     if ((drawEntity->Level[8][this->G_Array[8] - 1] == 239 || drawEntity->Level[0][this->G_Array[9] - 1] == 239 || drawEntity->Level[0][this->G_Array[10] - 1] == 239) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->RecieverRolling(false);
        }
    else if ((drawEntity->Level[8][this->G_Array[8] - 1] == 255 || drawEntity->Level[0][this->G_Array[9] - 1] == 255 || drawEntity->Level[0][this->G_Array[10] - 1] == 255) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->RecieverRolling(false);
        }
    else if ((drawEntity->Level[8][this->G_Array[8] - 1] == 116 || drawEntity->Level[0][this->G_Array[9] - 1] == 116 || drawEntity->Level[0][this->G_Array[10] - 1] == 116) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->RecieverRolling(false);
        }
    else if ((drawEntity->Level[8][this->G_Array[8] - 1] == 100 || drawEntity->Level[0][this->G_Array[9] - 1] == 100 || drawEntity->Level[0][this->G_Array[10] - 1] == 100) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->RecieverRolling(false);
        }
    else if ((drawEntity->Level[8][this->G_Array[8] - 1] == 18 || drawEntity->Level[0][this->G_Array[9] - 1] == 18 || drawEntity->Level[0][this->G_Array[10] - 1] == 18) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->RecieverRolling(false);
        }
    else if ((drawEntity->Level[8][this->G_Array[8] - 1] == 34 || drawEntity->Level[0][this->G_Array[9] - 1] == 34 || drawEntity->Level[0][this->G_Array[10] - 1] == 34) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->RecieverRolling(false);
        }

    
    //Vertical
    if ((drawEntity->Level[0][this->G_Array[5]] == 0 || drawEntity->Level[0][this->G_Array[9]] == 0) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 0 || drawEntity->Level[0][this->G_Array[9]] == 0) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630) )
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 1 || drawEntity->Level[0][this->G_Array[9]] == 1) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 1 || drawEntity->Level[0][this->G_Array[9]] == 1) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 2 || drawEntity->Level[0][this->G_Array[9]] == 2) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 2 || drawEntity->Level[0][this->G_Array[9]] == 2) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 87 || drawEntity->Level[0][this->G_Array[9]] == 87) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 87 || drawEntity->Level[0][this->G_Array[9]] == 87) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 86 || drawEntity->Level[0][this->G_Array[9]] == 86) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 86 || drawEntity->Level[0][this->G_Array[9]] == 86) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 223 || drawEntity->Level[0][this->G_Array[9]] == 223) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 223 || drawEntity->Level[0][this->G_Array[9]] == 223) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 12 || drawEntity->Level[0][this->G_Array[9]] == 12) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 12 || drawEntity->Level[0][this->G_Array[9]] == 12) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 84 || drawEntity->Level[0][this->G_Array[9]] == 84) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 84 || drawEntity->Level[0][this->G_Array[9]] == 84) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
    }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 13 || drawEntity->Level[0][this->G_Array[9]] == 13) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 13 || drawEntity->Level[0][this->G_Array[9]] == 13) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 117 || drawEntity->Level[0][this->G_Array[9]] == 117) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 117 || drawEntity->Level[0][this->G_Array[9]] == 117) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 84 || drawEntity->Level[0][this->G_Array[9]] == 84) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 84 || drawEntity->Level[0][this->G_Array[9]] == 84) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 192 || drawEntity->Level[0][this->G_Array[9]] == 192) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 192 || drawEntity->Level[0][this->G_Array[9]] == 192) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 193 || drawEntity->Level[0][this->G_Array[9]] == 193) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 193 || drawEntity->Level[0][this->G_Array[9]] == 193) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[5]] == 194 || drawEntity->Level[0][this->G_Array[9]] == 194) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }
    else if ((drawEntity->Level[0][this->G_Array[6]] == 194 || drawEntity->Level[0][this->G_Array[9]] == 194) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
    {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
        );
        }



        //Vertical---> Level[4]
        if ((drawEntity->Level[4][this->G_Array[5]] != 2 || drawEntity->Level[4][this->G_Array[9]] != 2) && !(player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
        {
            this->player->resetVelocityY();
            this->player->setPosition(
                this->player->getGlobalBounds().left,
                this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
            );
        }
        else if ((drawEntity->Level[4][this->G_Array[6]] != 2 || drawEntity->Level[4][this->G_Array[9]] != 2) && (player->getDir()) && (this->Quad[0].y >= 0 && this->Quad[4].y < 630))
        {
            this->player->resetVelocityY();
            this->player->setPosition(
                this->player->getGlobalBounds().left,
                this->Grid[5].y * this->drawEntity->tileSize - this->player->getGlobalBounds().height
            );
        }
}

void Game::updateText()
{
    std::stringstream ss;
    ss << this->coinCount;
    sf::View currentView = window->getView();
    InGameText.setPosition(currentView.getCenter().x + 80.f - currentView.getSize().x / 2, currentView.getCenter().y + 12.f - currentView.getSize().y / 2);
    this->InGameText.setString(ss.str());
}

void Game::update()
{
    // Polling window events
    while (this->window->pollEvent(this->ev))
    {
       
        if (this->ev.type == sf::Event::Closed)
        {
                this->window->close();
        }
        else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
        {
                this->window->close();
        }

        if (this->ev.type == sf::Event::KeyReleased &&
                (this->ev.key.code == sf::Keyboard::A ||
                    this->ev.key.code == sf::Keyboard::D ||
                    this->ev.key.code == sf::Keyboard::W ||
                    this->ev.key.code == sf::Keyboard::S ||
                    this->ev.key.code == sf::Keyboard::J ||
                    this->ev.key.code == sf::Keyboard::C ||
                    this->ev.key.code == sf::Keyboard::Backspace
                    )
                )
        {
          this->player->resetAnimationTimer();
        }
            if (currentState == GameState::MENU) {
                top3ScoreTexts.clear();
                topScoreTexts.clear();
                gui->handleEvent(this->ev);
               
                // Check if the PLAY button was clicked
                if (this->gui->isStart) {
                    currentState = GameState::GAMEPLAY; // Switch to GAMEPLAY state
                    gameClock.restart(); // Start the game clock
                    gameStarted = true; // Mark the game as started
                }
                std::ifstream inputFile("./Score/Score.txt");
                std::vector<std::pair<std::string, int>> scores;

                if (inputFile.is_open())
                {
                    std::string name;
                    int score;
                    while (inputFile >> name >> score)
                    {
                        scores.emplace_back(name, score);
                    }
                    inputFile.close();
                }
                else
                {
                    std::cerr << "Failed to open scores.txt" << std::endl;
                }
                std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
                    return a.second > b.second;
                    });
                int maxScoreWidth = 0;
                for (const auto& score : scores)
                {
                    int scoreWidth = std::to_string(score.second).length();
                    if (scoreWidth > maxScoreWidth)
                    {
                        maxScoreWidth = scoreWidth;
                    }
                }

                for (size_t i = 0; i < std::min<size_t>(scores.size(), 5); i++)
                {
                    sf::Text text;
                    sf::Text score_text;
                    text.setFont(font);
                    text.setFillColor(sf::Color::Black);
                    text.setCharacterSize(60);

                    score_text.setFont(font);
                    score_text.setFillColor(sf::Color::Black);
                    score_text.setCharacterSize(60);
                    // Calculate the padding based on the maximum score width
                    int padding = maxScoreWidth - std::to_string(scores[i].second).length();

                    // Create a string with the appropriate padding
                    std::string paddedScore = std::string(padding, ' ') + std::to_string(scores[i].second);

                    text.setString(scores[i].first );
                    score_text.setString(paddedScore);
                    text.setPosition(960, 170 + i * 70);
                    score_text.setPosition(1200, 170 + i * 70);
                    top3ScoreTexts.push_back(text);
                    topScoreTexts.push_back(score_text);
                }
            
  
            }
            else if (this->currentState == GameState::SAVE_GAME)
            {
                this->gameStarted = false;
                if (ev.type == sf::Event::TextEntered)
                {
                    if (ev.text.unicode < 128)
                    {
                        if (ev.text.unicode == 8 && !inputText.empty())
                        {
                            // Handle backspace
                            inputText.pop_back();
                        }
                        else if (ev.text.unicode == 13)
                        {

                            // Handle Enter key (newline) and save to a text file
                            inputText += '\n';
                            std::ofstream file("./Score/Score.txt", std::ios::app);
                            if (file.is_open())
                            {
                                file << inputText << score << '\n';
                                file.close();
                                this->gui->isHelp = false;
                                this->gui->isAbout = false;
                                this->gui->isMenu = true;
                                this->gui->isStart = false;
                                this->inputText = "";
                                this->Restart = false;
                                this->currentState = GameState::MENU;
                            }
                            else
                            {
                                std::cerr << "Error opening file for writing." << std::endl;
                            }
                        }
                        else if (inputText.length() < 8) // Limit input to 8 characters
                        {
                            // Append the typed character to the inputText
                            inputText += static_cast<char>(ev.text.unicode);
                        }
                    }
                }
                this->Name_text.setPosition(350, 400);
                this->Name_text.setString( "YOUR NAME : " + this->inputText);
            }
    }

    if (currentState == GameState::GAMEPLAY) {
        sf::Vector2f playerPosition = player->getPosition();
        this->elapsedTime = gameClock.getElapsedTime().asSeconds();
        if (playerPosition.x >= 720 && playerPosition.x <= 18480)
        {
            if (playerPosition.y < 315 - this->player->getGlobalBounds().height / 2)
            {
                view.setCenter(playerPosition.x, playerPosition.y + this->player->getGlobalBounds().height / 2);
            }
            else
            {
                view.setCenter(playerPosition.x, view.getCenter().y);
            }
        }
        
        if ((this->player->getGlobalBounds().top >= 630.f || this->player->getHP() <= 0) && !this->gameDelay)
        {
            DelayTimer.restart();
            this->gameDelay = true;
        }
        else if(this->boss->getHP() <= 0 && !this->gameDelay)
        {
            DelayTimer.restart();
            this->gameDelay = true;
        }

        if (this->gameDelay && DelayTimer.getElapsedTime() >= DelayDuration && (this->player->getGlobalBounds().top >= 630.f || this->player->getHP() <= 0))
        {
            currentState = GameState::GAMEOVER;
            this->player->setPosition(0, 0);
        }
        else if (this->gameDelay && DelayTimer.getElapsedTime() >= DelayDuration && this->boss->getHP() <= 0)
        {
            currentState = GameState::VICTORY;
            this->player->setPosition(0, 0);
        }
        this->window->setView(view);
        // Polling window events and other logic here.
        // this->window->setView(view);
        float playerVelocityX = this->player->getVelocityX(); // Get the player's X velocity.
        this->updateCollision();
        this->updatePlayer();
        this->updateCoin();
        this->updateText();
        this->updateEyeguy();
        this->updateBoss();
    }
    else if (this->currentState == GameState::GAMEOVER)
    {
        this->score = this->coinCount;
        std::stringstream ss;
        ss << "Press enter to continue ...";
        this->GO_text.setString(ss.str()); if (ev.key.code == sf::Keyboard::Enter)
        {
            this->currentState = GameState::SAVE_GAME;
        }
    }
    else if(this->currentState == GameState::VICTORY)
    {
        std::stringstream AA;
        AA << "Press enter to continue ...";
        this->GV_text.setString(AA.str());
        float multiple = (600 - this->elapsedTime) / 100;
        if (multiple < 1)
        {
            multiple = 1;
        }
        this->score = multiple * this->coinCount; 
        if (ev.key.code == sf::Keyboard::Enter)
        {
            this->currentState = GameState::SAVE_GAME;
        }
    }
    else if (this->currentState == GameState::SAVE_GAME)
    {
        this->SAVE_text.setPosition(520, 200);
        std::stringstream CC;
        CC << " Score : " << this->score;
        this->SAVE_text.setString(CC.str());
        coins.clear();
        eyeguys.clear();
    }
    if (!this->Restart)
    {
        this->DelayTimer.restart();
        this->initGameOver();
        this->initVictory();
        this->initPlayer();
        this->initText();
        this->initCoin();
        this->initEyeguy();
        this->initBoss();
        this->elapsedTime = 0;
        view = this->window->getDefaultView();
        this->initialView = window->getView();

        drawEntity = new DrawEntity(*window);
        
        this->Restart = true;
    }
}

void Game::renderGUI()
{
    gui->draw();
    if (this->gui->isMenu)
    {
        for (const sf::Text& text : top3ScoreTexts)
        {
            window->draw(text);
        }
        for (const sf::Text& score_text : topScoreTexts)
        {
            window->draw(score_text);
        }
    }
    
}
void Game::renderEntity()
{
    this->drawEntity->render();
}
void Game::renderCoin()
{
    for (auto* coin : this->coins)
    {
        coin->Render(this->window);
    }
    window->draw(coinIcon);
}
void Game::renderEyeguy()
{
    for (auto* eyeguy : this->eyeguys)
    {
        eyeguy->Render(this->window);
    }
}
void Game::renderPlayer()
{
    this->player->render(*window);
}

void Game::renderBoss()
{
    this->boss->Render(*window);
}

void Game::renderText()
{
    window->draw(this->InGameText);
}

void Game::renderGO()
{
    window->draw(this->GO[0]);
    window->draw(this->GO_text);
}

void Game::renderSaveGame()
{
    window->draw(this->SAVE_text);
    window->draw(this->Name_text);
}

void Game::renderVIC()
{
    window->draw(this->Vic);
    window->draw(this->GV_text);
}

void Game::render()
{
    this->window->clear();

    if (currentState == GameState::GAMEPLAY) {
        // Your gameplay rendering logic here
        renderEntity();
        renderCoin();
        renderPlayer();
        renderEyeguy();
        renderBoss();
        renderText();
    }
    else {
        // Reset to the initial view for other states
        this->window->setView(initialView);

        if (currentState == GameState::MENU) {
            renderGUI();
        }
        else if (currentState == GameState::GAMEOVER)
        {
            renderGO();
        }
        else if (currentState == GameState::VICTORY)
        {
            renderVIC();
        }
        else if (currentState == GameState::SAVE_GAME)
        {
            renderSaveGame();
        }
    }

    
    this->window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
    return *this->window;
}

