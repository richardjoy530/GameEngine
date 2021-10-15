#pragma once

#include <windows.h>
#include "Graphics.h"

class Player
{
	// --------- TODO ---------
	// Position - DONE
	// Shooter direction - DONE
	// Brush player and bullet - DONE
	// Update() - DONE
	// Health
	// Score
	// --------- TODO ---------
public:
	Player();
	~Player();
	void Init(HWND hwnd);
	void Update(Graphics* graphics);

	FLOAT x, y; // Postion of the player
	FLOAT xAim, yAim; // Position to fire (to get the aiming direciton)
	FLOAT xSpeed, ySpeed;
	FLOAT health;
	FLOAT score;
	RECT playableArea;
};
