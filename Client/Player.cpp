#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"

#include <iostream>
#include <math.h>
#include <time.h>

Player::Player()
{
	pos_aim.x = pos_aim.y = 0;
	health = 100;
	score = 0;
}

void Player::Init(HWND hwnd)
{
	GetClientRect(hwnd, &playableArea);

	srand(time(nullptr));
	position.x = rand() % playableArea.right;
	position.y = rand() % playableArea.bottom;
    prev_position.x = position.x;
    prev_position.y = position.y;
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
		if (wParam == VK_UP || wParam == 0x57) { direction.up = false; }
		if (wParam == VK_DOWN || wParam == 0x53) { direction.down = false; }
		if (wParam == VK_RIGHT || wParam == 0x44) { direction.right = false; }
		if (wParam == VK_LEFT || wParam == 0x41) { direction.left = false; }

	    // Exit game if 'Q' or 'ESC' is pressed
		if (wParam == 0x51 || wParam == 0x1B)
		{
		    PostQuitMessage(0);
		}
	}
    else if (msg == WM_KEYDOWN)
    {
        if (wParam == VK_UP || wParam == 0x57) { direction.up = true; }
        if (wParam == VK_DOWN || wParam == 0x53) { direction.down = true; }
        if (wParam == VK_RIGHT || wParam == 0x44) { direction.right = true; }
        if (wParam == VK_LEFT || wParam == 0x41) { direction.left = true; }
    }
}

void Player::Update()
{
    if (direction.right == true && direction.left == false)
    {
        prev_position.x = position.x;

        if (frame < 100)
        {
            position.x += accleration * frame++;
        }
        else
        {
            position.x += accleration * frame;
        }
    }
    else if (direction.left == true && direction.right == false)
    {
        prev_position.x = position.x;

        if (frame < 100)
        {
            position.x -= accleration * frame++;
        }
        else
        {
            position.x -= accleration * frame;
        }
    }
    else if (direction.right == false && direction.left == false)
    {
        if (frame > 0)
        {
            if (prev_position.x < position.x)
            {
                position.x += accleration * frame--;
                frame--;
            }
            if (prev_position.x > position.x)
            {
                position.x -= accleration * frame--;
                frame--;
            }
        }
    }
	for (INT index = 0; index < 5; index++) { bullets[index].Update(); }
}

void Player::OnHit() {}
