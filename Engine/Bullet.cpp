#include "Bullet.h"
#include <math.h>

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
		if (position.x > playableArea.right) { position.x = 0; }
		if (position.y > playableArea.bottom) { position.y = 0; }
		if (position.x < 0) { position.x = playableArea.right; }
		if (position.y < 0) { position.y = playableArea.bottom; }

		position.x += cos(angle) * speed;
		position.y += sin(angle) * speed;
	}
}

//void Bullet::operator=(Bullet src)
//{
//	position.x = src.position.x;
//	position.y = src.position.y;
//	speed = src.speed;
//	isAlive = src.isAlive;
//	color = src.color;
//}
