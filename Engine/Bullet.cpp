#include "Bullet.h"

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