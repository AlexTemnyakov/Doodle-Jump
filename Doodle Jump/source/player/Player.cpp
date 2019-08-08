#include "Player.h"
#include <thread>

Rectangle collisions(Player* p, set<Block*> blocks);
Rectangle hasGround(Player* p, set<Block*> blocks);

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
	if (moveX > 0)
	{
		dir = true;
		if (x + width + moveX < u.W_WIDTH)
		{
			x += moveX;
			Rectangle c = collisions(this, blocks);
			if (c.x != -1)
			{
				printf("Collision moveX > 0\n");
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
	else if (moveX < 0)
	{
		dir = false;
		if (x + moveX > 0)
		{
			x += moveX;
			Rectangle c = collisions(this, blocks);
			if (c.x != -1)
			{
				printf("Collision moveX < 0\n");
				//this_thread::sleep_for(2s);
				printf("Before %d after %d\n", x - moveX, c.x + c.width + 1);
				//x = c.x + c.width + 1;
				x -= moveX;
				return;
			}
		}
		else
		{
			x = 0;
		}
	}

	if (moveY < 0)
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
		/*y += moveY;
		Rectangle c = collisions(this, blocks);
		if (c.x != -1)
		{
			printf("Collision moveY > 0\n");
			y = c.y - height - 1;
			return;
		}*/
	}
}

void Player::update(set<Block*> blocks)
{
	if (hasGround(this, blocks).x == -1)
	{
		if (!jumping)
		{
			y += 15;
			Rectangle r = hasGround(this, blocks);
			if (r.x != -1)
			{
				y = r.y - height - 1;
			}
		}
		else
		{
			printf("Jumping...\n");
			if (jumpTimer == 0)
			{
				jumpTimer = t.milliseconds();
			}
			else
			{
				jumpTotalTime = t.milliseconds() - jumpTimer;
				jumpTimer = t.milliseconds();
			}

			int jumpRange = 0;
			if (jumpDist < 100)
			{
				y -= 12;
				jumpDist += 12;
				jumpRange = 12;
			}
			else if (jumpDist < 180)
			{
				y -= 8;
				jumpDist += 8;
				jumpRange = 8;
			}
			else if (jumpDist < 220)
			{
				y -= 3;
				jumpDist += 3;
				jumpRange = 3;
			}
			else
			{
				printf("End of jumping\n");
				jumping = false;
				jumpDist = 0;
				jumpTimer = 0;
				jumpTotalTime = 0;
				return;
			}

			if (collisions(this, blocks).x != -1)
			{
				y += jumpRange;
				jumpDist = 0;
				jumping = false;
				jumpTotalTime = 0;
				jumpTimer = 0;

			}
			printf("Jumping time: %d\n", jumpTotalTime);
		}
	}
	else
	{
		if (jumping)
		{
			printf("Jumping...\n");
			if (jumpTimer == 0)
			{
				jumpTimer = t.milliseconds();
			}
			else
			{
				jumpTotalTime = t.milliseconds() - jumpTimer;
				jumpTimer = t.milliseconds();
			}

			if (jumpDist < 100)
			{
				y -= 15;
				jumpDist += 15;
			}
			else if (jumpDist < 180)
			{
				y -= 8;
				jumpDist += 8;
			}
			else if (jumpDist < 220)
			{
				y -= 3;
				jumpDist += 3;
			}
			else
			{
				printf("End of jumping\n");
				jumping = false;
				jumpDist = 0;
				jumpTimer = 0;
				jumpTotalTime = 0;
			}
			printf("Jumping time: %d\n", jumpTotalTime);
		}
	}
}

void Player::jump(set<Block*> blocks)
{
	if (hasGround(this, blocks).x != -1 && jumpDist == 0 && jumpTimer == 0)
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

Rectangle collisions(Player* p, set<Block*> blocks)
{
	for (auto b : blocks)
	{
		if (rectOverlap(p->getRectangle(), b->getRectangle()))
		{
			Rectangle r = b->getRectangle();
			return r;
		}
	}
	return { -1 };
}

Rectangle hasGround(Player* p, set<Block*> blocks)
{
	for (auto b : blocks)
	{
		bool yInRange = (p->getY() + p->getHeight() + 1 >= b->getY()) && (p->getY() + p->getHeight() + 1 <= b->getY() + b->getHeight());
		bool xInRange = ((p->getX() >= b->getX()) && (p->getX() <= b->getX() + b->getWidth())) || ((p->getX() + p->getWidth() >= b->getX()) && (p->getX() + p->getWidth() <= b->getX() + b->getWidth()));
		if (xInRange && yInRange)
		{
			return b->getRectangle();
		}
	}
	return { -1 };
}
