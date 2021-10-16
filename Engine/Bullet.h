#pragma once
#include "Interfaces.h"
#include "Direction.h"

class Bullet : public IGameObject
{
	FLOAT speed = 10;

public:
	BOOL isAlive = FALSE;
	D2D1_POINT_2F firePosition;
	D2D1_POINT_2F aimPostion;
	FLOAT angle = 0;
	D2D1_POINT_2F position;
	D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.3f, 0.0f);
	RECT playableArea = {};

	void Render(Graphics* graphics);
	void Update();

	//void operator = (Bullet src);
};
