#define IS_KEY_PRESSED(key)						(1 << 15) & GetAsyncKeyState(key)
#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

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

void Player::Init(HWND hwnd)
{
	GetClientRect(hwnd, &playableArea);
	bullets[0] = Bullet(x, y);
	bullets[1] = Bullet(x, y);
	bullets[2] = Bullet(x, y);
	bullets[3] = Bullet(x, y);
	bullets[4] = Bullet(x, y);
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(x, y, 10, color);
	graphics->DrawEllipse(xAim, yAim, 2, color);
	graphics->DrawLine(x, y, xAim, yAim, 2, color);
}

void Player::Fire() {}

bool Player::GetNextBullet(Bullet* bullet) { return false; }

void Player::OnWinEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_MOUSEMOVE)
	{
		xAim = GET_X_LPARAM(lParam);
		yAim = GET_Y_LPARAM(lParam);
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
	if (x > playableArea.right) { x = 0; }
	if (y > playableArea.bottom) { y = 0; }
	if (x < 0) { x = playableArea.right; }
	if (y < 0) { y = playableArea.bottom; }
	x += xSpeed;
	y += ySpeed;
}
