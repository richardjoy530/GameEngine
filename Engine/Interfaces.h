#pragma once
#include "Graphics.h"

class IGameObject
{
public:
	virtual void Render(Graphics* graphics) {}
	virtual void Update() {}
};
