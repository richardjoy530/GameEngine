#pragma once

#include "Interfaces.h"

class Target : public IGameObject
{
public:
	D2D1_POINT_2F position;
	D2D1_RECT_F rect;
	FLOAT health = 100;
	D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.0f, 0.0f);

	Target();

	void Init();

	void Render(Graphics* graphics);

	void Update();

	void OnHit();
};
