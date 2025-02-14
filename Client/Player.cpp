#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"

#include <ctime>
#include <iostream>

Player::Player()
{
	pos_aim_.x = pos_aim_.y = 0;
}

void Player::Init(const HWND handle)
{
	GetClientRect(handle, &playable_area_);

	srand(time(nullptr));
	position.x = rand() % playable_area_.right;
	position.y = rand() % playable_area_.bottom;
    prev_position.x = position.x;
    prev_position.y = position.y;
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(position.x, position.y, 10, color_);
	graphics->DrawEllipse(pos_aim_.x, pos_aim_.y, 2, color_);

	for (auto& bullet : bullets)
	{
	    bullet.Render(graphics);
	}
}

void Player::Fire()
{
	trigger_released_ = FALSE;
	Bullet bullet;
	bullet.isAlive = TRUE;
	bullet.aimPostion = pos_aim_;
	bullet.firePosition = position;
	bullet.angle = atan2f((pos_aim_.y - position.y), (pos_aim_.x - position.x));
	bullet.position = position;
	bullet.playableArea = playable_area_;
	bullet.color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
	GetNextBullet(bullet);
}

void Player::ResetBullets()
{
	for (auto& bullet : bullets)
	{
	    bullet.isAlive = FALSE;
	}
}

bool Player::GetNextBullet(const Bullet& bullet)
{
	for (auto& index : bullets)
    {
		if (!index.isAlive)
		{
            index = bullet;
			return TRUE;
		}
	}
	return FALSE;
}

void Player::OnWinEvent(const UINT msg, const WPARAM w_param, const LPARAM l_param)
{
	if (msg == WM_MOUSEMOVE)
	{
		pos_aim_.x = GET_X_LPARAM(l_param);
		pos_aim_.y = GET_Y_LPARAM(l_param);
	}
	else if (msg == WM_KEYDOWN && w_param == VK_SPACE && trigger_released_)
	{
		Fire();
	}
	else if (msg == WM_LBUTTONDOWN)
	{
		Fire();
		trigger_released_ = TRUE;
	}
	else if (msg == WM_KEYDOWN && w_param == 0x52)	// R => 0x52
	{
		ResetBullets();
	}
	else if (msg == WM_KEYUP)
	{
		if (w_param == VK_SPACE) { trigger_released_ = TRUE; }
		if (w_param == VK_UP || w_param == 0x57) { direction_.up = false; }
		if (w_param == VK_DOWN || w_param == 0x53) { direction_.down = false; }
		if (w_param == VK_RIGHT || w_param == 0x44) { direction_.right = false; }
		if (w_param == VK_LEFT || w_param == 0x41) { direction_.left = false; }

	    // Exit game if 'Q' or 'ESC' is pressed
		if (w_param == 0x51 || w_param == 0x1B)
		{
		    PostQuitMessage(0);
		}
	}
    else if (msg == WM_KEYDOWN)
    {
        if (w_param == VK_UP || w_param == 0x57) { direction_.up = true; }
        if (w_param == VK_DOWN || w_param == 0x53) { direction_.down = true; }
        if (w_param == VK_RIGHT || w_param == 0x44) { direction_.right = true; }
        if (w_param == VK_LEFT || w_param == 0x41) { direction_.left = true; }
    }
}

void Player::Update()
{
    if (direction_.right == true && direction_.left == false)
    {
        prev_position.x = position.x;

        if (frame_ < 100)
        {
            position.x += acceleration_ * static_cast<float>(frame_++);
        }
        else
        {
            position.x += acceleration_ * static_cast<float>(frame_);
        }
    }
    else if (direction_.left == true && direction_.right == false)
    {
        prev_position.x = position.x;

        if (frame_ < 100)
        {
            position.x -= acceleration_ * static_cast<float>(frame_++);
        }
        else
        {
            position.x -= acceleration_ * static_cast<float>(frame_);
        }
    }
    else if (direction_.right == false && direction_.left == false)
    {
        if (frame_ > 0)
        {
            if (prev_position.x < position.x)
            {
                position.x += acceleration_ * static_cast<float>(frame_--);
                frame_--;
            }
            if (prev_position.x > position.x)
            {
                position.x -= acceleration_ * static_cast<float>(frame_--);
                frame_--;
            }
        }
    }

	for (auto& bullet : bullets)
	{
	    bullet.Update();
	}
}
