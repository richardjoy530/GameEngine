#include "Bullet.h"

Bullet::Bullet() {}

void Bullet::Render(Graphics* graphics)
{
	if (isAlive)
	{
		graphics->DrawEllipse(x, y, 10, color);
	}
}

void Bullet::Update()
{
	if (isAlive)
	{

	}
}

void Bullet::operator=(Bullet src)
{
	x = src.x;
	y = src.y;
	speed = src.speed;
	isAlive = src.isAlive;
	color = src.color;
}
