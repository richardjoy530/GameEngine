#pragma once
#include "Interfaces.h"
#include "Direction.h"

class Bullet : public IGameObject
{
	D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.3f, 0.0f);
	FLOAT x = NULL;
	FLOAT y = NULL;

public:

	FLOAT speed = 50;
	BOOL isAlive = FALSE;

	Bullet();
	Bullet(FLOAT _x, FLOAT _y) { x = _x; y = _y; }

	void Render(Graphics* graphics);
	void Update();

	void operator = (Bullet src);
};
