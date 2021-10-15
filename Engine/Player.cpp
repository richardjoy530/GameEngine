#include "Player.h"

Player::Player()
{
	x = y = 200;
	xAim = yAim = 200;
	health = 100;
	score = 0;
	xSpeed = 0;
	ySpeed = 0;
}

Player::~Player() {}

void Player::Init(HWND hwnd)
{
	GetClientRect(hwnd, &playableArea);
}

void Player::Update(Graphics* graphics)
{
	if (x > playableArea.right) { x = 0; }
	if (y > playableArea.bottom) { y = 0; }
	if (x < 0) { x = playableArea.right; }
	if (y < 0) { y = playableArea.bottom; }
	x += xSpeed;
	y += ySpeed;
	graphics->DrawEllipse(x, y, 10);
	graphics->DrawEllipse(xAim, yAim, 2);
	graphics->DrawLine(x, y, xAim, yAim, 2);
}
