#pragma once

#include <d2d1.h>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
public:
	Graphics();
	~Graphics();

	bool Init(HWND hwnd);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b) { renderTarget->Clear(D2D1::ColorF(r, g, b)); }
};