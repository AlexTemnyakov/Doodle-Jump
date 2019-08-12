#include "Player.h"
#include <thread>

Rectangle* collisions(Player* p, set<Block*> blocks);
Rectangle* hasGround(Player* p, set<Block*> blocks);

Player::Player(const char* texturePath, int w, int h, int _x, int _y, SDL_Renderer* renderer)
{
	Utils u;
	textureLeft = new Texture(u.playersTextureLeftPath, w, h, renderer);
	textureRight = new Texture(u.playersTextureRightPath, w, h, renderer);
	width = w;
	height = h;
	x = _x;
	y = _y;
	dir = true;
	totalDistCurrent = 0;
	totalDistMax = 0;
}

Player::~Player()
{
	textureLeft->~Texture();
	textureRight->~Texture();
}

void Player::render(SDL_Renderer* renderer)
{
	if (dir) 
		textureRight->render(renderer, x, y);
	else
		textureLeft->render(renderer, x, y);
}

void Player::move(int moveX, int moveY, set<Block*> blocks)
{
	if (moveX > 0) // move to the right
	{
		dir = true;
		if (x + width + moveX < u.W_WIDTH)
		{
			x += moveX;
			Rectangle* c = collisions(this, blocks);
			if (c != NULL)
			{
				//printf("Collision moveX > 0\n");
				//x = c.x - width - 1;
				x -= moveX;
				return;
			}
		}
		else
		{
			x = u.W_WIDTH - width;
		}
	}
	else if (moveX < 0) // move to the left
	{
		dir = false;
		if (x + moveX > 0)
		{
			x += moveX;
			Rectangle* c = collisions(this, blocks);
			if (c != NULL)
			{
				//printf("Collision moveX < 0\n");
				x -= moveX;
				return;
			}
		}
		else
		{
			x = 0;
		}
	}

	/*if (moveY < 0)
	{
		if (y + moveY > 0)
		{
			y += moveY;
			Rectangle c = collisions(this, blocks);
			if (c.x != -1)
			{
				printf("Collision moveY < 0\n");
				y = c.y + c.height + 1;
				return;
			}
		}
		else
			y = 0;
	}
	else
	{
		y += moveY;
		Rectangle c = collisions(this, blocks);
		if (c.x != -1)
		{
			printf("Collision moveY > 0\n");
			y = c.y - height - 1;
			return;
		}
	}*/
}

void Player::update(set<Block*> blocks)
{
	int yPrev = y;
	int shift = 0;
	if (jumping)
	{
		//printf("Jumping... Distance %d\n", jumpDist);
		if (jumpTimer == 0)
		{
			jumpTimer = t.milliseconds();
		}
		else
		{
			jumpTotalTime = t.milliseconds() - jumpTimer;
			jumpTimer = t.milliseconds();
		}

		// because of shifting the world if the player is above than 1/3 part of the window,
		// we need to avoid extension of the jump
		shift = (y < u.W_HEIGHT / 3) ? 8 : 0;
		// how long the player has jumped
		int jumpRange = 0;
		if (jumpDist < 80)
		{
			y -= 10;
			jumpDist += 10 + shift;
			jumpRange = 10;
		}
		else if (jumpDist < 220)
		{
			y -= 8;
			jumpDist += 8 + shift;
			jumpRange = 8;
		}
		else if (jumpDist < 280)
		{
			y -= 5;
			jumpDist += 5 + shift;
			jumpRange = 5;
		}
		else
		{
			//printf("End of jumping\n");
			jumping = false;
			jumpDist = 0;
			jumpTimer = 0;
			jumpTotalTime = 0;
			jumpRange = 0;
			return;
		}

		// if there is a collision, move the player back
		if (collisions(this, blocks) != NULL)
		{
			y += jumpRange;
			jumpDist = 0;
			jumping = false;
			jumpTotalTime = 0;
			jumpTimer = 0;
			jumpRange = 0;
		}
	}
	else
	{
		jump(blocks);
		// free fall
		if (hasGround(this, blocks) == NULL)
		{
			y += 15;
			Rectangle* r = hasGround(this, blocks);
			if (r != NULL)
			{
				y = r->y - height - 1;
			}
		}
	}
	int dist = yPrev - (y - shift);
	totalDistCurrent += dist;
	if (totalDistCurrent > totalDistMax)
		totalDistMax = totalDistCurrent;
}

void Player::jump(set<Block*> blocks)
{
	if (hasGround(this, blocks) != NULL && jumpDist == 0 && jumpTimer == 0)
	{
		jumping = true;
	}
}

Rectangle Player::getRectangle()
{
	Rectangle r = { x, y, width, height };
	return r;
}

int Player::getY()
{
	return y;
}

int Player::getX()
{
	return x;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

int Player::getTotalDistance()
{
	return totalDistMax;
}

Rectangle* collisions(Player* p, set<Block*> blocks)
{
	for (auto b : blocks)
	{
		if (rectOverlap(p->getRectangle(), b->getRectangle()))
		{
			Rectangle* r = &b->getRectangle();
			return r;
		}
	}
	return NULL;
}

Rectangle* hasGround(Player* p, set<Block*> blocks)
{
	for (auto b : blocks)
	{
		bool yInRange = (p->getY() + p->getHeight() + 1 >= b->getY()) && (p->getY() + p->getHeight() + 1 <= b->getY() + b->getHeight());
		bool xInRange = ((p->getX() >= b->getX()) && (p->getX() <= b->getX() + b->getWidth())) || ((p->getX() + p->getWidth() >= b->getX()) && (p->getX() + p->getWidth() <= b->getX() + b->getWidth()));
		if (xInRange && yInRange)
		{
			Rectangle r = b->getRectangle();
			b->setTouched();
			return &r;
		}
	}
	return NULL;
}
