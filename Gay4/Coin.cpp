#include "Coin.h"

void Coin::initVariable()
{
	this->currentFrame = sf::IntRect(0, 0, 16, 16);
}

void Coin::initSprite()
{
	this->sprite.scale(2.f, 2.f);
	this->sprite.setTextureRect(this->currentFrame);
}

void Coin::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;

}

Coin::Coin(sf::Texture* texture, float pos_X, float pos_Y)
{
	this->initVariable();
	this->textures = texture;
	this->initVariable();
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_X, pos_Y);
	
}

Coin::~Coin()
{
}


const sf::Sprite Coin::getSprite() const
{
	return this->sprite;
}

const bool& Coin::getAnimSwitch() const
{
	bool anim_switch = this->animationSwitch;
	return anim_switch;
}


const sf::FloatRect Coin::getGlobalBounds() const
{
	return  this->sprite.getGlobalBounds();
}

void Coin::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Coin::Update()
{
	
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.075f || this->getAnimSwitch()) {
		this->currentFrame.left += 16.f;
		if (this->currentFrame.left >= 80.f )
		{
			
			if (this->currentFrame.top == 0)
			{
				this->currentFrame.top += 16.f;
				this->currentFrame.left = 0.f;
			}
			else
			{
				this->currentFrame.top = 0;
				int randomFrame = std::rand() % 5;
				this->currentFrame.left = randomFrame * 16.f;
			}
		}
		this->animationTimer.restart();
		this->sprite.setScale(2.f, 2.f);
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Coin::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
