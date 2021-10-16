#define IS_KEY_PRESSED(key)						(1 << 15) & GetAsyncKeyState(key)
#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"
#include <math.h>

Player::Player()
{
	position.x = position.y = 200;
	aimPosition.x = aimPosition.y = 200;
	health = 100;
	score = 0;
	xSpeed = 0;
	ySpeed = 0;
}

void Player::Init(HWND hwnd)
{
	GetClientRect(hwnd, &playableArea);
	bullets[0] = Bullet(position.x, position.y);
	bullets[1] = Bullet(position.x, position.y);
	bullets[2] = Bullet(position.x, position.y);
	bullets[3] = Bullet(position.x, position.y);
	bullets[4] = Bullet(position.x, position.y);
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(position.x, position.y, 10, color);
	graphics->DrawEllipse(aimPosition.x, aimPosition.y, 2, color);
	graphics->DrawLine(position.x, position.y, aimPosition.x, aimPosition.y, 2, color);

	bullets[0].Render(graphics);
}

void Player::Fire()
{
	bullets[0].isAlive = TRUE;
	bullets[0].aimPostion = aimPosition;
	bullets[0].firePosition = position;
	bullets[0].angle = atan2f((aimPosition.y - position.y), (aimPosition.x - position.x));
	bullets[0].position = position;
	bullets[0].color = D2D1::ColorF((FLOAT)(rand() % 100) / (FLOAT)100, (FLOAT)(rand() % 100) / (FLOAT)100, (FLOAT)(rand() % 100) / (FLOAT)100);
}

bool Player::GetNextBullet(Bullet* bullet) { return false; }

void Player::OnWinEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEMOVE)
	{
		aimPosition.x = GET_X_LPARAM(lParam);
		aimPosition.y = GET_Y_LPARAM(lParam);
	}
	else if ((msg == WM_KEYDOWN && wParam == VK_SPACE) || msg == WM_LBUTTONDOWN)
	{
		Fire();
	}
	else if (msg == WM_KEYUP)
	{
		if (wParam == VK_UP || wParam == 0x57) { ySpeed = 0; }
		if (wParam == VK_DOWN || wParam == 0x53) { ySpeed = 0; }
		if (wParam == VK_RIGHT || wParam == 0x44) { xSpeed = 0; }
		if (wParam == VK_LEFT || wParam == 0x41) { xSpeed = 0; }
	}
}

// KeyDown is detected by GetAsyncKeyState() because the KeyDown event
// fired by windows has a delay for continuious presses where the key is not released
// TODO : Make a toggling logic in Player::OnWinEvent()
void Player::GetKeyUpdates()
{
	ySpeed = 0;
	xSpeed = 0;

	// W => 0x57
	if (IS_KEY_PRESSED(VK_UP) || IS_KEY_PRESSED(0x57)) { ySpeed += -speed; }

	// S => 0x53
	if (IS_KEY_PRESSED(VK_DOWN) || IS_KEY_PRESSED(0x53)) { ySpeed += speed; }

	// A => 0x41
	if (IS_KEY_PRESSED(VK_LEFT) || IS_KEY_PRESSED(0x41)) { xSpeed += -speed; }

	// D => 0x44
	if (IS_KEY_PRESSED(VK_RIGHT) || IS_KEY_PRESSED(0x44)) { xSpeed += speed; }
}

void Player::Update()
{
	GetKeyUpdates();
	if (position.x > playableArea.right) { position.x = 0; }
	if (position.y > playableArea.bottom) { position.y = 0; }
	if (position.x < 0) { position.x = playableArea.right; }
	if (position.y < 0) { position.y = playableArea.bottom; }
	position.x += xSpeed;
	position.y += ySpeed;

	bullets[0].Update();
}
