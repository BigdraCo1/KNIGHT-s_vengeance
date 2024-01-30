#include "Boss.h"
#include <random>

sf::Texture Boss::loadTexture(const std::string& filePath)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filePath))
	{
		std::cout << "ERROR: Texture not found at path: " << filePath << "\n";
	}
	return texture;
}

void Boss::initTexture()
{
	this->animationTextures[BOSS_ANIMATION_STATES::B_IDLE]				= loadTexture("./Boss/idle2.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_ATTACK_ONE]		= loadTexture("./Boss/A_1.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_ATTACK_TWO]		= loadTexture("./Boss/A_2.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_DEATH]				= loadTexture("./Boss/death.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_WARP]				= loadTexture("./Boss/skill1.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_IDLE_LEFT]			= loadTexture("./Boss/idle2_Left.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_ATTACK_ONE_LEFT]	= loadTexture("./Boss/A_1_LEFT.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_ATTACK_TWO_LEFT]	= loadTexture("./Boss/A_2_LEFT.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_DEATH_LEFT]		= loadTexture("./Boss/B_Death_LEFT.png");
	this->animationTextures[BOSS_ANIMATION_STATES::B_WARP_LEFT]			= loadTexture("./Boss/skill1_Left.png");
	this->animationTextures[BOSS_ANIMATION_STATES::TRANSPARENT]			= loadTexture("./Boss/A_2_LEFT.png");
	this->empty_bar_texture												= loadTexture("./Boss/Boss_bar.png");
	this->Health_bar_texture											= loadTexture("./Boss/Boss_H.png");
}

void Boss::initVariable()
{
	this->Hpmax		= 35;
	this->Hp		= this->Hpmax;
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->Left		= true;
	this->Shift		= 100.f;
	this->Near		= false; 
	this->Warped	= false;
	this->Over		= true;
	this->Attacked	= false;
}

void Boss::initSprite()
{
	this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_IDLE_LEFT]);
	this->currentFrame = sf::IntRect(0, 0, 100, 100);
	this->sprite.setPosition(11800, 350);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.0f, 3.0f);
	this->sprite.setOrigin(0.f, 0.f);

	this->empty_bar.setTexture(this->empty_bar_texture);
	this->Health_bar.setTexture(this->Health_bar_texture);

	if (Hpmax != 0)
	{
		this->empty_bar.setScale(3.f, 3.f);
		this->Health_bar.setScale(3.f * Hp / Hpmax, 3.f);
	}
	this->empty_bar.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4, this->sprite.getPosition().y );
	this->Health_bar.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4, this->sprite.getPosition().y + 8.f);
}

void Boss::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->attackTimer_1.restart();
	this->attackTimer_2.restart();
}


Boss::Boss(Player* player)
{
	this->initVariable();
	this->initTexture();
	this->initAnimation();
	this->initSprite();
	this->player = player;
}

Boss::~Boss()
{
}

const sf::Sprite Boss::getSprite() const
{
    return this->sprite;
}

const bool& Boss::getAnimSwitch() const
{
	return this->animationSwitch;
}

const bool& Boss::getState() const
{
  
}
int Boss::getHP() const {

	return this->Hp;
}
const sf::FloatRect Boss::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

const bool& Boss::makeDamage()
{
   
}

void Boss::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Boss::UpdateMovement()
{
	this->empty_bar.setScale(4.f, 4.f);
	this->Health_bar.setScale(4.f * Hp / Hpmax, 4.f);
	this->empty_bar.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4, this->sprite.getPosition().y);
	this->Health_bar.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4, this->sprite.getPosition().y + 4.f);
	if (this->player->getPosition().x + this->player->getGlobalBounds().width / 2 < this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2)
	{
		this->Left = true;
	}
	else
	{
		this->Left = false;
	}

	if (this->player->getPosition().x + this->player->getGlobalBounds().width / 2 >= this->sprite.getPosition().x && this->player->getPosition().x + this->player->getGlobalBounds().width / 2 <= this->sprite.getPosition().x + this->sprite.getGlobalBounds().width &&
		this->player->getPosition().y + this->player->getGlobalBounds().height / 2 >= this->sprite.getPosition().y && this->player->getPosition().y + this->player->getGlobalBounds().height / 2 <= this->sprite.getPosition().y + this->sprite.getGlobalBounds().height)
	{
		this->Near = true;
	}
	else
	{
		this->Near = false;
	}

	if (Collision::pixelPerfectTest(this->sprite, this->player->getSprite()))
	{
		if (this->player->getCurrentFrame().left == 360 && (this->player->getAnimstate() == 13) && HitTimer.getElapsedTime() >= HitDuration)
		{
			HitTimer.restart();
			this->Hp -= 1;
			std::cout << Hp << std::endl;
		}
		else if (this->player->getCurrentFrame().left == 240 && (this->player->getAnimstate() == 12) && HitTimer.getElapsedTime() >= HitDuration)
		{
			HitTimer.restart();
			this->Hp -= 1;
			std::cout << Hp << std::endl;
		}
	}
	if (this->player->getPosition().x >= 8800)
	{
		if (this->Death)
		{
			this->currentFrame = sf::IntRect(0, 100, 100, 100);
			this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::TRANSPARENT]);
			this->sprite.setTextureRect(this->currentFrame);
		}
		else if (this->Hp <= 0)
		{
			if (this->Left)
			{
				//this->currentFrame = sf::IntRect(900, 0, 100, 100);
				this->animState = BOSS_ANIMATION_STATES::B_DEATH_LEFT;
			}
			else
			{
				
				this->animState = BOSS_ANIMATION_STATES::B_DEATH;
			}
		}
		else if (!this->Warped && warpTimer.getElapsedTime() >= warpDuration)
		{
			this->warpTimer.restart();
			if (this->Left)
			{
				this->animState = BOSS_ANIMATION_STATES::B_WARP_LEFT;
				
			}
			else
			{
				this->currentFrame = sf::IntRect(0, 0, 100, 100);
				this->animState = BOSS_ANIMATION_STATES::B_WARP;
			}
		}
		else if (this->Warped && this->Near)
		{
			if ( attackTimer_2.getElapsedTime() >= attack_2Duration)
			{
				this->attackTimer_2.restart();
				if (this->Left)
				{
					this->currentFrame = sf::IntRect(500, 0 , 100,100);
					this->animState = BOSS_ANIMATION_STATES::B_ATTACK_ONE_LEFT;
				}
				else
				{
					this->currentFrame = sf::IntRect(0, 0, 100, 100);
					this->animState = BOSS_ANIMATION_STATES::B_ATTACK_ONE;
				}
			}
		}
		
	}
	else
	{
		if (this->Left)
		{
			this->animState = BOSS_ANIMATION_STATES::B_IDLE_LEFT;

		}
		else
		{
			this->animState = BOSS_ANIMATION_STATES::B_IDLE;
		}
	}
}

void Boss::UpdateAnimation()
{
	if (this->animState == BOSS_ANIMATION_STATES::B_DEATH) {
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_DEATH]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left == 1000.f && this->currentFrame.top == 0 )
			{
				this->currentFrame.top += 100.f; this->currentFrame.left = 0.f;
			}
			if (this->currentFrame.left >= 800.f && this->currentFrame.top == 100.f)
			{
				this->Shift = 0.f;
				this->Death = true;
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == BOSS_ANIMATION_STATES::B_DEATH_LEFT) {
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_DEATH_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -100 && this->currentFrame.top == 0)
			{
				this->currentFrame.top += 100.f; this->currentFrame.left = 900.f;
			}
			if (this->currentFrame.left <= 800.f && this->currentFrame.top == 100.f)
			{
				this->Shift = 0.f;
				this->Death = true;
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == BOSS_ANIMATION_STATES::B_ATTACK_ONE) {
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_ATTACK_ONE]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 600.f)
			{
				this->currentFrame.left = 0;
				this->Warped = false;
			}
			if ( this->currentFrame.left == 3 * this->Shift)
			{
					if (Collision::pixelPerfectTest(this->sprite, this->player->getSprite()))
					{
						this->player->takeDamage(6);
					}
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == BOSS_ANIMATION_STATES::B_ATTACK_ONE_LEFT) {
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_ATTACK_ONE_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -this->Shift && this->currentFrame.top == 0)
			{
				this->currentFrame.left = 500.f;
				this->Warped = false;
			}
			if (this->currentFrame.left == 2 * this->Shift )
			{
				if (Collision::pixelPerfectTest(this->sprite, this->player->getSprite()))
				{
					this->player->takeDamage(6);
				}
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == BOSS_ANIMATION_STATES::B_WARP  ) {
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_WARP]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left == 600.f && this->currentFrame.top == 0)
			{
				this->currentFrame.top += 100.f; this->currentFrame.left = 0.f;
			}
			else if(this->currentFrame.left == 600.f && this->currentFrame.top != 0)
			{
				this->currentFrame.top -= 100.f; this->currentFrame.left = 0.f;
				this->Warped = true;
			}
			if (this->currentFrame.left == 100.f && this->currentFrame.top == 100.f)
			{
				if (this->Near)
				{
					std::default_random_engine generator(static_cast<unsigned int>(time(nullptr))); // Initialize random engine once

					// Set up distributions for x and y separately
					std::uniform_real_distribution<float> xDistribution(player->getPosition().x - 600, player->getPosition().x - 200);
					std::uniform_real_distribution<float> yDistribution(player->getPosition().y - player->getGlobalBounds().height, player->getPosition().y - player->getGlobalBounds().height / 2);

					// Generate random x and y values
					float rand_x = xDistribution(generator);
					float rand_y = yDistribution(generator);

					this->sprite.setPosition(rand_x, rand_y);
				}
				else
				{
					this->sprite.setPosition(player->getPosition().x + player->getGlobalBounds().width / 4, player->getPosition().y - player->getGlobalBounds().height / 2);
					this->Near = true;
				}
				
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == BOSS_ANIMATION_STATES::B_WARP_LEFT ) {
		
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_WARP_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -this->Shift && this->currentFrame.top == 0)
			{
				this->currentFrame.top += 100.f; this->currentFrame.left = 500.f;
			}
			else if (this->currentFrame.left <= -this->Shift && this->currentFrame.top != 0)
			{
				this->currentFrame.top -= 100.f; this->currentFrame.left = 500.f;
				this->Warped = true;
			}
			
			if (this->currentFrame.left == 400.f && this->currentFrame.top == 100.f)
			{
				if (this->Near)
				{
					std::default_random_engine generator(static_cast<unsigned int>(time(nullptr))); // Initialize random engine once

					// Set up distributions for x and y separately
					std::uniform_real_distribution<float> xDistribution(player->getPosition().x + 200, player->getPosition().x + 500);
					std::uniform_real_distribution<float> yDistribution(player->getPosition().y - player->getGlobalBounds().height, player->getPosition().y - player->getGlobalBounds().height / 2);

					// Generate random x and y values
					float rand_x = xDistribution(generator);
					float rand_y = yDistribution(generator);

					this->sprite.setPosition(rand_x, rand_y);
				}
				else
				{
					this->sprite.setPosition(player->getPosition().x - player->getGlobalBounds().width / 4, player->getPosition().y - player->getGlobalBounds().height / 2);
					this->Near = true;
				}
				
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	
	else if (this->animState == BOSS_ANIMATION_STATES::B_IDLE) {
		this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_IDLE]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f) {
			this->currentFrame.left += this->Shift;
			
			if (this->currentFrame.left >= 400.f && this->currentFrame.top == 0)
			{
				this->currentFrame.top = 100.f; this->currentFrame.left = 0;
			}
			if (this->currentFrame.left >= 400.f && this->currentFrame.top != 0)
			{
				this->currentFrame.top = 0.f; this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == BOSS_ANIMATION_STATES::B_IDLE_LEFT) {
			this->sprite.setTexture(this->animationTextures[BOSS_ANIMATION_STATES::B_IDLE_LEFT]);
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f) {
				this->currentFrame.left -= this->Shift;
				
				if (this->currentFrame.left <= - this->Shift && this->currentFrame.top == 0)
				{
					this->currentFrame.top = 100.f; this->currentFrame.left = 3 * this->Shift;
				}
				if (this->currentFrame.left <= -this->Shift && this->currentFrame.top != 0)
				{
					this->currentFrame.top = 0.f; this->currentFrame.left = 3 * this->Shift;
				}
				this->animationTimer.restart();
				this->sprite.setScale(3.f, 3.f);
				this->sprite.setTextureRect(this->currentFrame);
			}
	}
}

void Boss::Update()
{
	this->UpdateMovement();
	this->UpdateAnimation();
}

void Boss::Render(sf::RenderTarget& target)
{
	if (!this->Death)
	{
		target.draw(this->sprite);
		target.draw(this->empty_bar);
		target.draw(this->Health_bar);
	}
}
