#pragma once

#include <windows.h>
#include "Bullet.h"
#include "Utilities/Struct.h"

class Player : public GameObject
{
	D2D1_COLOR_F color_ = D2D1::ColorF(0.0f, 1.0f, 1.0f);
	D2D1_POINT_2F pos_aim_;
	BOOL trigger_released_ = TRUE;
	RECT playable_area_;

    // Consider this as time/ticks/seconds
    int frame_ = 0;

    // this needs to be calculated when user presses arrow keys.
    // this will be a constant value. Also, this needs x and y component
    float acceleration_ = 0.3F;
    PlayerDirection direction_;

public:

	D2D1_POINT_2F position;
	D2D1_POINT_2F prev_position;
	Bullet bullets[5];

	Player();

	void Init(HWND handle);

	void Update();

	void Render(Graphics* graphics);

	void OnWinEvent(UINT msg, WPARAM w_param, LPARAM l_param);

	bool GetNextBullet(const Bullet& bullet);

	void Fire();

	void ResetBullets();

    void CalculateAcceleration();

    void CalculateVelocity();

    void CalculatePosition();
};
