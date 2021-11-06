#define IS_KEY_PRESSED(key)						(1 << 15) & GetAsyncKeyState(key)
#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"
#include <math.h>
#include <time.h>

Player::Player()
{
	pos_aim.x = pos_aim.y = 0;
	health = 100;
	score = 0;
	speed_dir.x = 0;
	speed_dir.y = 0;
}

void Player::Init(HWND hwnd)
{
	GetClientRect(hwnd, &playableArea);

	srand(time(nullptr));
	position.x = rand() % playableArea.right;
	position.y = rand() % playableArea.bottom;
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(position.x, position.y, 10, color);
	graphics->DrawEllipse(pos_aim.x, pos_aim.y, 2, color);

	for (INT index = 0; index < 5; index++) { bullets[index].Render(graphics); }
}

void Player::Fire()
{
	trigger_released = FALSE;
	Bullet bullet;
	bullet.isAlive = TRUE;
	bullet.aimPostion = pos_aim;
	bullet.firePosition = position;
	bullet.angle = atan2f((pos_aim.y - position.y), (pos_aim.x - position.x));
	bullet.position = position;
	bullet.playableArea = playableArea;
	bullet.color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
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
		pos_aim.x = GET_X_LPARAM(lParam);
		pos_aim.y = GET_Y_LPARAM(lParam);
	}
	else if (msg == WM_KEYDOWN && wParam == VK_SPACE && trigger_released)
	{
		Fire();
	}
	else if (msg == WM_LBUTTONDOWN)
	{
		Fire();
		trigger_released = TRUE;
	}
	else if (msg == WM_KEYDOWN && wParam == 0x52)	// R => 0x52
	{
		ResetBullets();
	}
	else if (msg == WM_KEYUP)
	{
		if (wParam == VK_SPACE) { trigger_released = TRUE; }
		if (wParam == VK_UP || wParam == 0x57) { speed_dir.y = 0; }
		if (wParam == VK_DOWN || wParam == 0x53) { speed_dir.y = 0; }
		if (wParam == VK_RIGHT || wParam == 0x44) { speed_dir.x = 0; }
		if (wParam == VK_LEFT || wParam == 0x41) { speed_dir.x = 0; }
	}
}

// KeyDown is detected by GetAsyncKeyState() because the KeyDown event
// fired by windows has a delay for continuious presses where the key is not released
// TODO : Make a toggling logic in Player::OnWinEvent()
void Player::GetKeyUpdates()
{
	speed_dir.x = 0;
	speed_dir.y = 0;

	// W => 0x57
	if (IS_KEY_PRESSED(VK_UP) || IS_KEY_PRESSED(0x57)) { speed_dir.y -= speed_val; }

	// S => 0x53
	if (IS_KEY_PRESSED(VK_DOWN) || IS_KEY_PRESSED(0x53)) { speed_dir.y += speed_val; }

	// A => 0x41
	if (IS_KEY_PRESSED(VK_LEFT) || IS_KEY_PRESSED(0x41)) { speed_dir.x -= speed_val; }

	// D => 0x44
	if (IS_KEY_PRESSED(VK_RIGHT) || IS_KEY_PRESSED(0x44)) { speed_dir.x += speed_val; }

	if (abs(speed_dir.x) + abs(speed_dir.y) != 0)
	{
		FLOAT magnitude = sqrtf(((speed_dir.x * speed_dir.x) + (speed_dir.y * speed_dir.y)));
		speed_dir.x = speed_val * (speed_dir.x / magnitude);
		speed_dir.y = speed_val * (speed_dir.y / magnitude);
	}
}

void Player::Update()
{
	GetKeyUpdates();
	if (position.x > playableArea.right) { position.x = playableArea.right - speed_dir.x; }
	if (position.y > playableArea.bottom) { position.y = playableArea.bottom - speed_dir.y; }
	if (position.x < 0) { position.x = -speed_dir.x; }
	if (position.y < 0) { position.y = -speed_dir.y; }

	position.x += speed_dir.x;
	position.y += speed_dir.y;

	for (INT index = 0; index < 5; index++) { bullets[index].Update(); }
}

void Player::OnHit() {}
