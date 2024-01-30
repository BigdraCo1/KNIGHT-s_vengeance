#include "Eyeguy.h"
#include "Collision.h"
sf::Texture Eyeguy::loadTexture(const std::string& filePath)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filePath))
	{
		std::cout << "ERROR: Texture not found at path: " << filePath << "\n";
	}
	return texture;
}
void Eyeguy::initTexture()
{
	this->animationTextures[EYEGUY_ANIMATION_STATES::FLIGTH] = loadTexture("./Enemy/Flight.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::ATTACK] = loadTexture("./Enemy/Attack.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::ATTACK_LEFT] = loadTexture("./Enemy/Attack_Left.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::FLIGTH_LEFT] = loadTexture("./Enemy/Flight_Left.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::TAKE_HIT_LEFT] = loadTexture("./Enemy/Take_Hit_Left.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::TAKE_HIT] = loadTexture("./Enemy/Take_Hit.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::DEATH] = loadTexture("./Enemy/Death.png");
	this->animationTextures[EYEGUY_ANIMATION_STATES::DEATH_LEFT] = loadTexture("./Enemy/Death_Left.png");
}
void Eyeguy::initVariable(int speed)
{
	this->Left = false;
	this->ChaseSpeed = speed * 0.1f;
	this->Damage = false;
	this->Hp = 3;
	this->Death = false;
	this->Hit = false;
}

void Eyeguy::initSprite()
{
	this->sprite.scale(1.f, 1.f);
	this->currentFrame = sf::IntRect(0, 0, 150, 150);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::FLIGTH]);
}

void Eyeguy::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->attackTimer.restart();
}

Eyeguy::Eyeguy( float pos_X, float pos_Y , int speed , Player* player, DrawEntity* Entity)
{
	this->player = player;
	this->initVariable(speed);
	this->initSprite();
	this->initTexture();
	this->initAnimation();
	this->sprite.setPosition(pos_X, pos_Y);
}

Eyeguy::~Eyeguy()
{
}


const sf::Sprite Eyeguy::getSprite() const
{
	return this->sprite;
}

const bool& Eyeguy::getAnimSwitch() const
{
	bool anim_switch = this->animationSwitch;
	return anim_switch;
}

const bool& Eyeguy::getState() const
{
	return this->Death;
}


const sf::FloatRect Eyeguy::getGlobalBounds() const
{
	return  this->sprite.getGlobalBounds();
}

const bool& Eyeguy::makeDamage()
{
	return this->Damage;
}

void Eyeguy::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->attackTimer.restart();
}

void Eyeguy::UpdateMovement(sf::Vector2f playerPositionCenter, sf::Vector2f playerPositionLeft, sf::Vector2f playerPositionRight, bool Chase , bool player_dir)
{
	this->SpriteCenter = sf::Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
	if (Hp <= 0)
	{	//DEATH
		this->sprite.move(0, 0);
		this->attackTimer.restart();
		if (this->Left) {
			this->animState = EYEGUY_ANIMATION_STATES::DEATH_LEFT;
		}
		else {
			this->animState = EYEGUY_ANIMATION_STATES::DEATH;
		}
		this->Hit = false;
	}
	else if (Chase && this->player->left && (this->SpriteCenter.x >= this->player->getPosition().x && this->SpriteCenter.x <= this->player->getPosition().x + this->player->getGlobalBounds().width /2) && this->SpriteCenter.y <= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height
		&& this->SpriteCenter.y >= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2)
	{
		
		this->sprite.move(dir * this->ChaseSpeed);
		
		if (Collision::pixelPerfectTest(this->sprite, this->player->getSprite()))
		{
				if (this->player->getCurrentFrame().left == 360 && (this->player->getAnimstate() == 13) && !this->Hit)
				{
					this->dir = playerPositionCenter - this->SpriteCenter;
					float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
						if (length != 0) 
						{
							dir /= length;
						}
						Hp -= 1; 
						if (Hp > 0)
						{
							this->attackTimer.restart();
							if (this->Left)
							{
								this->Hit = true;
								this->animState = EYEGUY_ANIMATION_STATES::TAKE_HIT_LEFT;
							}
							else
							{
								this->Hit = true;
								this->animState = EYEGUY_ANIMATION_STATES::TAKE_HIT;
							}
						}
						std::cout << Hp << std::endl;
				}
				else
				{
					if (attackTimer.getElapsedTime() >= attackCooldownDuration) 
					{

						this->attackTimer.restart();
						if (this->Left) 
						{
							this->animState = EYEGUY_ANIMATION_STATES::ATTACK_LEFT;
						}
						else 
						{
							this->animState = EYEGUY_ANIMATION_STATES::ATTACK;
						}
					}
				}
		}
		

	}
	else if (Chase && !this->player->left && (this->SpriteCenter.x <= this->player->getPosition().x + this->player->getGlobalBounds().width && this->SpriteCenter.x >= this->player->getPosition().x + this->player->getGlobalBounds().width / 2) && this->SpriteCenter.y <= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height
		&& this->SpriteCenter.y >= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2)
	{
		this->sprite.move(dir * this->ChaseSpeed);

		if (Collision::pixelPerfectTest(this->sprite, this->player->getSprite()))
		{
			if (this->player->getCurrentFrame().left == 240 && (this->player->getAnimstate() == 12) && !this->Hit)
			{
				this->dir = playerPositionCenter - this->SpriteCenter;
				float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (length != 0)
				{
					dir /= length;
				}
				Hp -= 1;
				if (Hp > 0)
				{
					this->attackTimer.restart();
					if (this->Left)
					{
						this->Hit = true;
						this->animState = EYEGUY_ANIMATION_STATES::TAKE_HIT_LEFT;
					}
					else
					{
						this->Hit = true;
						this->animState = EYEGUY_ANIMATION_STATES::TAKE_HIT;
					}
				}
				std::cout << Hp << std::endl;
				std::cout << Hp << std::endl;
			}
			else
			{
				if (attackTimer.getElapsedTime() >= attackCooldownDuration)
				{

					this->attackTimer.restart();
					if (this->Left)
					{
						this->animState = EYEGUY_ANIMATION_STATES::ATTACK_LEFT;
					}
					else
					{
						this->animState = EYEGUY_ANIMATION_STATES::ATTACK;
					}
				}
			}
		}


	}
	else if (this->sprite.getPosition().x > 8790)
	{
		this->animState = EYEGUY_ANIMATION_STATES::DEATH;
	}
	else if (Chase 
			&& this->SpriteCenter.y <= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height 
			&& this->SpriteCenter.y >= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2 
		    && (this->SpriteCenter.x <= playerPositionCenter.x  
			&& this->SpriteCenter.x >= playerPositionLeft.x + 25.f) 
			&& !player_dir && this->sprite.getPosition().x < 8800 )
	{

		this->sprite.move(0, 0);
		if (attackTimer.getElapsedTime() >= attackCooldownDuration) {
			
			this->attackTimer.restart();
			if (this->Left) {
				this->animState = EYEGUY_ANIMATION_STATES::ATTACK_LEFT;
			}
			else {
				this->animState = EYEGUY_ANIMATION_STATES::ATTACK;
			}
		}
		this->Hit = false;
	}
	else if (Chase && this->SpriteCenter.y <= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height 
				   && this->SpriteCenter.y >= this->player->getGlobalBounds().top + this->player->getGlobalBounds().height / 2 
				   && this->SpriteCenter.x >= playerPositionCenter.x													   
				   && this->SpriteCenter.x <= playerPositionRight.x - 25.f 
				   && player_dir && this->sprite.getPosition().x < 8800)
	{
		if (attackTimer.getElapsedTime() >= attackCooldownDuration) {

			this->attackTimer.restart();
			if (this->Left) {
				this->animState = EYEGUY_ANIMATION_STATES::ATTACK_LEFT;
			}
			else {
				this->animState = EYEGUY_ANIMATION_STATES::ATTACK;
			}
		}
		this->Hit = false;
		this->sprite.move(0, 0);
	}
	else if (Chase && this->sprite.getPosition().x < 8800) {
		if (this->ChaseSpeed < 0)
		{
			this->ChaseSpeed *= -1;
		}
		// Chase mode
		if (this->SpriteCenter.x > playerPositionCenter.x) {
			this->Left = true;
		}
		else {
			this->Left = false;
		}

		if (this->Left) {
			this->animState = EYEGUY_ANIMATION_STATES::FLIGTH_LEFT;
		}
		else {
			this->animState = EYEGUY_ANIMATION_STATES::FLIGTH;
		}

		this->dir = playerPositionCenter - this->SpriteCenter;
		float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (length != 0) {
			dir /= length;
		}
		this->sprite.move(dir * this->ChaseSpeed);
		this->Hit = false;
	}
	else 
	{
		// Non-chase mode - move to the left
		if (this->sprite.getPosition().x < 3280 || this->sprite.getPosition().x > 6500)
		{
			this->ChaseSpeed *= -1;
		}
		if (this->ChaseSpeed >= 0)
		{
			this->animState = EYEGUY_ANIMATION_STATES::FLIGTH_LEFT;
		}
		else
		{
			this->animState = EYEGUY_ANIMATION_STATES::FLIGTH;
		}
		this->sprite.move(sf::Vector2f(-1, 0.05) * this->ChaseSpeed); // Adjust the speed as needed
		this->Hit = false;
	}
}

void Eyeguy::UpdateAnimation()
{	
	if (this->animState == EYEGUY_ANIMATION_STATES::DEATH) {
		this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::DEATH]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.left += 150.f;
			if (this->currentFrame.left == 150.f)
			{
				while (this->sprite.getPosition().y + 2 * this->sprite.getGlobalBounds().height / 3 <= 590)
				{
					this->sprite.move(0, 1);
				}
			}
			if (this->currentFrame.left >= 600.f)
			{
				this->currentFrame.left = 0.f;
				this->Death = true;
			}
			
			this->animationTimer.restart();
			this->sprite.setScale(1.f, 1.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::DEATH_LEFT) {
		this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::DEATH_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			
			this->currentFrame.left -= 150.f;
			if (this->currentFrame.left == 300.f)
			{
				while (this->sprite.getPosition().y + 2 * this->sprite.getGlobalBounds().height / 3 <= 590)
				{
					this->sprite.move(0, 1);
				}
			}
			if (this->currentFrame.left <= -150.f)
			{
				this->currentFrame.left = 450.f;
				this->Death = true;
			}
			this->animationTimer.restart();
			this->sprite.setScale(1.f, 1.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::TAKE_HIT) {
	this->sprite.move(0, 0);
	this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::TAKE_HIT]);
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f ) {
		this->currentFrame.left += 150.f;
		if (this->currentFrame.left >= 600.f)
		{
			this->currentFrame.left = 0.f;
		}
		this->animationTimer.restart();
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setTextureRect(this->currentFrame);
	}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::TAKE_HIT_LEFT) {
	this->sprite.move(0, 0);
	this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::TAKE_HIT_LEFT]);
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
		
		this->currentFrame.left -= 150.f;
		if (this->currentFrame.left <= -150.f)
		{
			this->currentFrame.left = 450.f;
		}
		this->animationTimer.restart();
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setTextureRect(this->currentFrame);
	}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::FLIGTH) {
		this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::FLIGTH]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f) {
			this->currentFrame.left += 150.f;
			if (this->currentFrame.left >= 1200.f)
			{
				this->currentFrame.left = 0;
			}
			this->Damage = false;
			this->animationTimer.restart();
			this->sprite.setScale(1.f, 1.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::FLIGTH_LEFT) {
		this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::FLIGTH_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f) {
			this->currentFrame.left -= 150.f;
			if (this->currentFrame.left <= - 150.f)
			{
				this->currentFrame.left = 1050.f;
			}
			this->Damage = false;
			this->animationTimer.restart();
			this->sprite.setScale(1.f, 1.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::ATTACK) {
		this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::ATTACK]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f /this->ChaseSpeed) {
			this->currentFrame.left += 150.f;
			if (this->currentFrame.left == 1050.f && !this->Damage)
			{
				this->Damage = true;
				this->player->takeDamage(1);
			}
			if (this->currentFrame.left != 1050.f)
			{
				this->Damage = false;
			}
			if (this->currentFrame.left >= 1200.f)
			{
				this->currentFrame.left = 0.f; this->Damage = false;
			}
			this->animationTimer.restart();
			this->sprite.setScale(1.f, 1.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == EYEGUY_ANIMATION_STATES::ATTACK_LEFT) {
		this->sprite.setTexture(this->animationTextures[EYEGUY_ANIMATION_STATES::ATTACK_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f /this->ChaseSpeed ) {
			this->currentFrame.left -= 150.f;
			if (this->currentFrame.left == 0.f && !this->Damage)
			{
				this->Damage = true;
				this->player->takeDamage(1);
			}
			if (this->currentFrame.left != 0.f)
			{
				this->Damage = false;
			}
			if (this->currentFrame.left <= -150.f)
			{
				this->currentFrame.left = 1050.f; this->Damage = false;
			}
			this->animationTimer.restart();
			this->sprite.setScale(1.f, 1.f);
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}

void Eyeguy::Update(sf::Vector2f playerPositionCenter, sf::Vector2f playerPositionLeft, sf::Vector2f playerPositionRight, bool Chase, bool player_dir)
{
	this->UpdateMovement(playerPositionCenter , playerPositionLeft , playerPositionRight, Chase , player_dir);
	this->UpdateAnimation();

}

void Eyeguy::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}