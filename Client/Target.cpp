#include "Target.h"

void Target::Init()
{
	rect = { 200, 200, 220, 220 };
}

void Target::Render(Graphics* graphics)
{
	graphics->DrawRectangle(rect, color);
}

void Target::Update()
{
}

void Target::OnHit()
{
}
