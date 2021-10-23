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
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(position.x, position.y, 10, color);
	graphics->DrawEllipse(aimPosition.x, aimPosition.y, 2, color);
	//graphics->DrawLine(position.x, position.y, aimPosition.x, aimPosition.y, 2, color);

	for (INT index = 0; index < 5; index++) { bullets[index].Render(graphics); }
}

void Player::Fire()
{
	Bullet bullet;
	bullet.playableArea = playableArea;
	bullet.isAlive = TRUE;
	bullet.aimPostion = aimPosition;
	bullet.firePosition = position;
	bullet.angle = atan2f((aimPosition.y - position.y), (aimPosition.x - position.x));
	bullet.position = position;
	bullet.color = D2D1::ColorF((FLOAT)(rand() % 100) / (FLOAT)100, (FLOAT)(rand() % 100) / (FLOAT)100, (FLOAT)(rand() % 100) / (FLOAT)100);
	GetNextBullet(bullet);
}

void Player::ResetBullets()
{
	for (INT index = 0; index < 5; index++) { bullets[index].isAlive = FALSE; }
}

bool Player::GetNextBullet(Bullet bullet)
{
	for (INT index = 0; index < 5; index++)
	{
		if (!bullets[index].isAlive)
		{
			bullets[index] = bullet;
			return TRUE;
		}
	}
	return FALSE;
}

void Player::OnWinEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEMOVE)
	{
		aimPosition.x = GET_X_LPARAM(lParam);
		aimPosition.y = GET_Y_LPARAM(lParam);
	}
	else if (/*(msg == WM_KEYDOWN && wParam == VK_SPACE) ||*/ msg == WM_LBUTTONDOWN)
	{
		Fire();
	}
	else if (msg == WM_KEYDOWN && wParam == 0x52)
	{
		ResetBullets();
	}
	else if (msg == WM_KEYUP)
	{
		if (wParam == VK_SPACE) { Fire(); }
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
	if (IS_KEY_PRESSED(VK_UP) || IS_KEY_PRESSED(0x57)) { ySpeed -= speed; }

	// S => 0x53
	if (IS_KEY_PRESSED(VK_DOWN) || IS_KEY_PRESSED(0x53)) { ySpeed += speed; }

	// A => 0x41
	if (IS_KEY_PRESSED(VK_LEFT) || IS_KEY_PRESSED(0x41)) { xSpeed -= speed; }

	// D => 0x44
	if (IS_KEY_PRESSED(VK_RIGHT) || IS_KEY_PRESSED(0x44)) { xSpeed += speed; }

	if (abs(xSpeed) + abs(ySpeed) != 0)
	{
		FLOAT magnitude = sqrt(((xSpeed * xSpeed) + (ySpeed * ySpeed)));
		xSpeed = speed * (xSpeed / magnitude);
		ySpeed = speed * (ySpeed / magnitude);
	}
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

	for (INT index = 0; index < 5; index++) { bullets[index].Update(); }
}

void Player::OnHit() {}
