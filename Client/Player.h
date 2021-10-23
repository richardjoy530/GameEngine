#pragma once

#include <windows.h>
#include "Bullet.h"
#include <functional>

class Player : public IGameObject
{
	// --------- TODO ---------
	// Position - DONE
	// Shooter direction - DONE
	// Brush player and bullet - DONE
	// Update() - DONE
	// Health
	// Score
	// --------- TODO ---------
private:
	FLOAT speed = 10;
	const D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 1.0f);

public:
	D2D1_POINT_2F position;		// Postion of the player
	D2D1_POINT_2F aimPosition;	// Position to fire (to get the aiming direciton)
	FLOAT xSpeed = 0, ySpeed = 0;
	FLOAT health;
	FLOAT score;
	RECT playableArea = {};
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
