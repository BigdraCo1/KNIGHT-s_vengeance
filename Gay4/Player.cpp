#include "Player.h"
sf::Texture Player::loadTexture(const std::string& filePath)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filePath))
	{
		std::cout << "ERROR: Texture not found at path: " << filePath << "\n";
	}
	return texture;
}

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->Jumping = false;
	this->isAttacking = false;
	this->left = false;
	this->Moving = false;
	this->Crouching = false;
	this->Rolling = false;
	this->RollingStatus = true;
	this->Hpmax = 100;
	this->Hp = this->Hpmax;
	this->Spmax = 100;
	this->Sp = this->Spmax;
	this->Shift = 120.f;
}

void Player::initTexture()
{
	this->animationTextures[PLAYER_ANIMATION_STATES::IDLE] = loadTexture("./Player/_Idle.png");
	this->RnBTexture = loadTexture("./Player/redblue .png");
	this->RedTexture = loadTexture("./Player/red.png");
	this->BlueTexture = loadTexture("./Player/blue.png");
}
void Player::initHealthbar()
{
	//Set Texture
	this->RnB.setTexture(this->RnBTexture);
	this->Red.setTexture(this->RedTexture);
	this->Blue.setTexture(this->BlueTexture);

	//Set Size
	this->Hpmax = 100;
	this->Spmax = 200;
	if (Hpmax != 0 && Spmax != 0)
	{
		this->RnB.setScale(2.f, 2.f);
		this->Red.setScale(2.f * Hp / Hpmax, 2.f);
		this->Blue.setScale(2.f * Sp / Spmax, 2.f);
	}

	//Set POS
	this->RnB.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4 , this->sprite.getPosition().y);
	this->Red.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4, this->sprite.getPosition().y);
	this->Blue.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4, this->sprite.getPosition().y + 8.f);
}
void Player::initSprite()
{
	this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::IDLE]);
	this->currentFrame = sf::IntRect(0, 0,120, 80);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.0f, 2.0f);
	this->sprite.setOrigin(0.f, 0.f);
}

void Player::initAnimation()
{
		this->animationTimer.restart();
		this->animationSwitch = true;
		this->attackTimer.restart(); // Add this line
}

void Player::initPhysics()
{
	this->velocityMax = 8.f;
	this->velocityMin = 0.2f;
	this->acceleration = 0.5f;
	this->drag = 0.93f;
	this->gravity = 0.8f;
	this->velocityMaxY = 40.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initHealthbar();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();

	this->animationTextures[PLAYER_ANIMATION_STATES::IDLE_LEFT] = loadTexture("./Player/_Idle_Left.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::MOVING_RIGHT] = loadTexture("./Player/_Run.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::MOVING_LEFT] = loadTexture("./Player/image.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::JUMPING] = loadTexture("./Player/_Jump.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::JUMPING_LEFT] = loadTexture("./Player/_Jump_Left.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::FALLING] = loadTexture("./Player/_Fall.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::FALLING_LEFT] = loadTexture("./Player/_Fall_Left.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH] = loadTexture("./Player/_Crouch.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH_LEFT] = loadTexture("./Player/_Crouch_Left.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH_WALK] = loadTexture("./Player/_CrouchWalk.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH_WALK_LEFT] = loadTexture("./Player/_C_Left.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT] = loadTexture("./Player/_Attack2NoMovement_Left.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::STATSIMPATTACK] = loadTexture("./Player/_Attack2NoMovement.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::ROLLING] = loadTexture("./Player/_Dash.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::P_DEATH] = loadTexture("./Player/_Death.png");
	this->animationTextures[PLAYER_ANIMATION_STATES::P_DEATH_LEFT] = loadTexture("./Player/_Death_Left.png");
}


Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
	{
		this->animationSwitch = false;
	}

	return anim_switch;
}
const sf::IntRect Player::getCurrentFrame() const
{
	return this->currentFrame;
}

void Player::useStaminapoint(const int usSp)
{
	if (this->Sp > 0)
	{
		this->Sp -= usSp;
	}

	if (this->Sp < 0)
	{
		this->Sp = 0;
	}
	std::cout << Sp << std::endl;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds() ;
}

short Player::getAnimstate() const {

	return animState;
}

float Player::getVelocityX() const {

	return velocity.x;
}
int Player::getHP() const {

	return this->Hp;
}

void Player::takeDamage(const int damage)
{
	if (this->Hp > 0)
	{
		this->Hp -= damage;
	}

	if (this->Hp < 0)
	{
		this->Hp = 0;
	}
	std::cout << Hp << std::endl;
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

const bool& Player::getDir()
{
	return this->left;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

const sf::Sprite Player::getSprite() const
{
	return this->sprite;
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}


void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	this->velocity.y = dir_y;

	//Acceleration
	this->velocity.x += dir_x * this->acceleration;


	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag; // Apply drag to both x and y components
	;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
	{
		this->velocity.x = 0.f;
	}
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::RecieverRolling(bool Collision)
{
	this->RollingStatus = Collision;
}

void Player::updateMovement()
{
	this->Crouching = false;

		if (!this->left)
		{
			this->Moving = false;
			this->animState = PLAYER_ANIMATION_STATES::IDLE;
		}
		else
		{
			this->Moving = false;
			this->animState = PLAYER_ANIMATION_STATES::IDLE_LEFT;
		}
	if (this->Hp <= 0)
	{
		if (!this->left)
		{
			this->Moving = false;
			this->animState = PLAYER_ANIMATION_STATES::P_DEATH;
		}
		else
		{
			this->Moving = false;
			this->animState = PLAYER_ANIMATION_STATES::P_DEATH_LEFT;
		}
	}
	if (this->Hp > 0)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && RollingStatus) //Rolling 
		{
			this->velocityMax = 50.f;
			if (Hp <= 0)
			{
				this->sprite.move(0, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !Rolling && Sp >= 40)
			{
				this->left = false;
				this->animState = PLAYER_ANIMATION_STATES::ROLLING;

				this->Moving = true;
				this->Rolling = true;
				this->move(50.f, velocity.y);
				this->useStaminapoint(40);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !Rolling && Sp >= 40)
			{
				this->left = true;
				this->animState = PLAYER_ANIMATION_STATES::ROLLING_LEFT;


				this->Moving = true;
				this->Rolling = true;
				this->move(-50.f, velocity.y);
				this->useStaminapoint(40);

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && !isAttacking) {
			if (attackTimer.getElapsedTime() >= attackCooldownDuration) {
				std::cout << "J key pressed\n"; // Debug line
				std::cout << "Cooldown elapsed: " << attackTimer.getElapsedTime().asSeconds() << " seconds\n"; // Debug line

				this->attackTimer.restart();
				if (!this->left)
				{
					this->animState = PLAYER_ANIMATION_STATES::STATSIMPATTACK;
				}
				else
				{
					this->animState = PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT;
				}
				isAttacking = true;
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !(attackTimer.getElapsedTime() <= attackDuration)) //Left
		{
			this->velocityMax = 4.f;
			this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
			this->left = true;

			this->Moving = true;
			this->move(-1.f, velocity.y);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !(attackTimer.getElapsedTime() <= attackDuration)) //Right
		{
			this->velocityMax = 4.f;
			this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
			this->left = false;

			this->Moving = true;
			this->move(1.f, velocity.y);

		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			this->Rolling = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
			this->isAttacking = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !Jumping) //Top
		{
			this->move(velocity.x, -30.f);
			this->Moving = true;
			this->Jumping = true;
			if (!this->left)
			{
				this->animState = PLAYER_ANIMATION_STATES::JUMPING;
			}
			else
			{
				this->animState = PLAYER_ANIMATION_STATES::JUMPING_LEFT;
			}
		}
		if (attackTimer.getElapsedTime() <= attackDuration)
		{
			if (!(this->animState == PLAYER_ANIMATION_STATES::FALLING || this->animState == PLAYER_ANIMATION_STATES::FALLING_LEFT))
			{
				if (!this->left)
				{
					this->animState = PLAYER_ANIMATION_STATES::STATSIMPATTACK;
				}
				else
				{
					this->animState = PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT;
				}
			}
		}
		if (velocity.y > 0)
		{
			this->Moving = true;
			if (!this->left)
			{
				this->animState = PLAYER_ANIMATION_STATES::FALLING;
			}
			else
			{
				this->animState = PLAYER_ANIMATION_STATES::FALLING_LEFT;
			}
		}
		if (velocity.y == 0)
		{
			this->Jumping = false;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		{
			this->velocityMax = 0.5f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				this->animState = PLAYER_ANIMATION_STATES::CROUCH_WALK;
				this->left = false;

				this->Moving = true;
				this->move(0.5f, velocity.y);


			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				this->move(-0.5f, velocity.y);
				this->animState = PLAYER_ANIMATION_STATES::CROUCH_WALK_LEFT;
				this->left = true;


				this->Moving = true;
				this->move(-0.5f, velocity.y);

			}
			else
			{
				this->Moving = false;
				if (!this->left)
				{
					this->animState = PLAYER_ANIMATION_STATES::CROUCH;
				}
				else
				{
					this->animState = PLAYER_ANIMATION_STATES::CROUCH_LEFT;
				}
			}
		}
		else
		{
			this->Moving = false;
			this->velocityMax = 8.f;
		}
	}
}

void Player::updateAnimation()
{
	//std::cout << "Current animState: " << animState << std::endl;
	if (this->animState == PLAYER_ANIMATION_STATES::P_DEATH) {
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::P_DEATH]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 1200.f)
			{
				this->currentFrame.left = 0;
			}
			if (this->currentFrame.left == 1080)
			{
				this->Shift = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::P_DEATH_LEFT) {
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::P_DEATH_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -120.f)
			{
				this->currentFrame.left = 1080.f;
			}
			if (this->currentFrame.left == 0)
			{
				this->Shift = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::IDLE) {
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::IDLE]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
				this->currentFrame.left += this->Shift;
				if (this->currentFrame.left >= 1200.f)
				{
					this->currentFrame.left = 0;
				}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::CROUCH_WALK) {
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH_WALK]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 960.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::CROUCH_WALK_LEFT) {
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH_WALK_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -120.f)
			{
				this->currentFrame.left = 840;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::MOVING_RIGHT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 1200.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::MOVING_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -120.f)
			{
				this->currentFrame.left = 1080;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING )
	{
			this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::JUMPING]);
			if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
				this->currentFrame.left += this->Shift;
				if (this->currentFrame.left >= 360.f)
				{
					this->currentFrame.left = 0;
				}
				this->animationTimer.restart();
				this->sprite.setTextureRect(this->currentFrame);

			}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING_LEFT )
	{
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::JUMPING_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 360.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}

	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING_LEFT)
	{
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::JUMPING_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 360.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}

	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING )
	{
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::FALLING]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 360.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING_LEFT)
	{
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::FALLING_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimSwitch()) {
			this->currentFrame.left += this->Shift;
			if (this->currentFrame.left >= 360.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::STATSIMPATTACK ) {
        this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::STATSIMPATTACK]);
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.075f || this->getAnimSwitch()){
            // Loop through frames
                this->currentFrame.left += this->Shift;
                if (this->currentFrame.left >= 720.f) 
				{
					this->currentFrame.left = 0.f;
                }
                this->animationTimer.restart();
                this->sprite.setTextureRect(this->currentFrame);
        }
    }
	else if (this->animState == PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT) {
		 this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT]);
		 if (this->animationTimer.getElapsedTime().asSeconds() >= 0.075f || this->getAnimSwitch()) {
			 // Loop through frames
			 this->currentFrame.left -= this->Shift;
			 if (this->currentFrame.left <= -120.f)
			 {
				 this->currentFrame.left = 600.f;
			 }
			 this->animationTimer.restart();
			 this->sprite.setTextureRect(this->currentFrame);
		 }
		 }
	else if (this->animState == PLAYER_ANIMATION_STATES::CROUCH) {
		 this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH]);
		 if (this->animationTimer.getElapsedTime().asSeconds() >= 0.075f || this->getAnimSwitch()) {
			
			 this->currentFrame.left = 0.f;
			 this->animationTimer.restart();
			 this->sprite.setTextureRect(this->currentFrame);
		 }
		 }
	else if (this->animState == PLAYER_ANIMATION_STATES::CROUCH_LEFT) {
		 this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::CROUCH_LEFT]);
		 if (this->animationTimer.getElapsedTime().asSeconds() >= 0.075f || this->getAnimSwitch()) {
			 
			 this->currentFrame.left = 0.f;
			 this->animationTimer.restart();
			 this->sprite.setTextureRect(this->currentFrame);
		 }
		 }
	else if (this->animState == PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT) {
			 this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::STATSIMPLEATTACK_LEFT]);
			 if (this->animationTimer.getElapsedTime().asSeconds() >= 0.075f || this->getAnimSwitch()) {
				 // Loop through frames
				 this->currentFrame.left -= this->Shift;
				 if (this->currentFrame.left <= -120.f)
				 {
					 this->currentFrame.left = 600.f;
				 }
				 this->animationTimer.restart();
				 this->sprite.setTextureRect(this->currentFrame);
			 }
			 }
	else if (this->animState == PLAYER_ANIMATION_STATES::IDLE_LEFT) {
		this->sprite.setTexture(this->animationTextures[PLAYER_ANIMATION_STATES::IDLE_LEFT]);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame.left -= this->Shift;
			if (this->currentFrame.left <= -120.f)
			{
				this->currentFrame.left = 1080;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}


void Player::updateHealthbar()
{
	this->Hpmax = 100;
	this->Spmax = 100;
	if (this->RegenTimer.getElapsedTime().asSeconds() >= 0.002) {
		Sp = Sp + 0.08;
		this->RegenTimer.restart();
	}
	if (Sp > Spmax)
	{
		Sp = Spmax;
	}
	if (Hpmax != 0 && Spmax != 0)
	{
		this->RnB.setScale(2.f, 2.f);
		this->Red.setScale(2.f * Hp / Hpmax, 2.f);
		this->Blue.setScale(2.f * Sp / Spmax, 2.f);
	}

	this->RnB.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 32, this->sprite.getPosition().y);
	this->Red.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 32, this->sprite.getPosition().y + 2.f);
	this->Blue.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 32, this->sprite.getPosition().y + 16.f);

}

void Player::update()
{
	this->updateHealthbar();
	this->updateMovement();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	
	if (Hp > 0)
	{
		target.draw(this->Red);
		target.draw(this->Blue);
		target.draw(this->RnB);
	}
}

