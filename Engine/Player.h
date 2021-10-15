#pragma once

#include <windows.h>
#include "Graphics.h"
#include "Direction.h"
#include "Interfaces.h"
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
	FLOAT x, y;				// Postion of the player
	FLOAT xAim, yAim;		// Position to fire (to get the aiming direciton)
	FLOAT xSpeed, ySpeed;
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
	
	bool GetNextBullet(Bullet* bullet);
	
	void Fire();
};
