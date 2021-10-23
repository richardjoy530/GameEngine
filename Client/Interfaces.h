#pragma once
#include "Graphics.h"

class IGameObject
{
public:
	D2D1_POINT_2F position;
	virtual void Render(Graphics* graphics) {}
	virtual void Update() {}
	virtual void OnHit() {}
};
