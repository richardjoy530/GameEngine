#pragma once

#include <windows.h>
#include "Bullet.h"

class Player : public IGameObject
{
private:
	FLOAT speed_val = 10;
	const D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 1.0f);
	D2D1_POINT_2F pos_aim;
	FLOAT health;
	FLOAT score;
	D2D1_POINT_2F speed_dir;
	BOOL trigger_released = TRUE;
	RECT playableArea;

public:

	D2D1_POINT_2F position;
	Bullet bullets[5];

	Player();

	void Init(HWND hwnd);

	void Update();

	void Render(Graphics* graphics);

	void GetKeyUpdates();

	void OnWinEvent(UINT msg, WPARAM wParam, LPARAM lParam);

	bool GetNextBullet(Bullet bullet);

	void Fire();

	void ResetBullets();

	void OnHit();
};
