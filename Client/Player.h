#pragma once

#include <windows.h>
#include "Bullet.h"
#include "Utilities/Struct.h"

class Player : public IGameObject
{
    FLOAT accleration = 0.3;
    int frame = 0;
    PlayerDirection direction;
	const D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 1.0f);
	D2D1_POINT_2F pos_aim;
	FLOAT health;
	FLOAT score;
	BOOL trigger_released = TRUE;
	RECT playableArea;

public:

	D2D1_POINT_2F position;
	D2D1_POINT_2F prev_position;
	Bullet bullets[5];

	Player();

	void Init(HWND hwnd);

	void Update();

	void Render(Graphics* graphics);

	void OnWinEvent(UINT msg, WPARAM wParam, LPARAM lParam);

	bool GetNextBullet(Bullet bullet);

	void Fire();

	void ResetBullets();

	void OnHit();
};
