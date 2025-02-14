#pragma once

#include "Graphics.h"

class GameObject
{
public:
    virtual ~GameObject() = default;
    D2D1_POINT_2F position;
	virtual void Render(Graphics* graphics) {}
	virtual void Update() {}
};
