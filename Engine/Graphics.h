#pragma once

#include <d2d1.h>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 1.0f);
	ID2D1SolidColorBrush* brush;
	D2D1_ELLIPSE ellipse;

public:
	Graphics();
	~Graphics();

	bool Init(HWND hwnd);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b) { renderTarget->Clear(D2D1::ColorF(r, g, b)); }

	void DrawEllipse(FLOAT x, FLOAT y, int r);

	void DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT width);
};