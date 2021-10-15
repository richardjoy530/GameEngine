#pragma once
#include "Interfaces.h"
#include "Direction.h"

class Bullet : public IGameObject
{
	const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.3f, 0.0f);
	FLOAT x = 0;
	FLOAT y = 0;

public:
	Direction firingDirction;

	FLOAT speed = 50;
	BOOL isAlive = FALSE;

	// Bullet();

	void Render(Graphics* graphics);
	void Update();
};
