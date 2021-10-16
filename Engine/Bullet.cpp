#include "Bullet.h"
#include <math.h>

Bullet::Bullet() {}

void Bullet::Render(Graphics* graphics)
{
	if (isAlive)
	{
		graphics->DrawEllipse(position.x, position.y, 5, color);
	}
}

void Bullet::Update()
{
	if (isAlive)
	{
		position.x += cos(angle) * speed;
		position.y += sin(angle) * speed;
	}
}

void Bullet::operator=(Bullet src)
{
	position.x = src.position.x;
	position.y = src.position.y;
	speed = src.speed;
	isAlive = src.isAlive;
	color = src.color;
}
