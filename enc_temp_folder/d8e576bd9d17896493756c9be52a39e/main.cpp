#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Graphics.h"

Graphics* graphics; // The Almighty gfx

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

FLOAT x = 200, y = 200;
FLOAT xDisplacement = 0;
FLOAT yDisplacement = 0;
FLOAT speed = 10;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(
		CLASS_NAME,
		0,
		NULL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // x, y, width, height - TODO: Make it adaptive fullscreen
		NULL,
		NULL,
		hInstance,
		NULL
	);


	if (hwnd == NULL)	return 1;

	SetWindowLong(hwnd, GWL_STYLE, 0); // Remove all window styles, basically removes the border and close|min|max buttons .. i hate those

	graphics = new Graphics();

	if (!graphics->Init(hwnd))
	{
		delete graphics;
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	RECT rcWind;
	GetClientRect(hwnd, &rcWind);



	// Run the message loop.
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		// If there is a message, then handle the message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
		// Update
		graphics->BeginDraw();
		graphics->ClearScreen(0, 0, 0);
		if (x > rcWind.right)
		{
			x = 0;
		}if (x < 0)
		{
			x = rcWind.right;
		}if (y < 0)
		{
			y = rcWind.bottom;
		}if (y > rcWind.bottom)
		{
			y = 0;
		}
		x += xDisplacement;
		y += yDisplacement;
		graphics->DrawEllipse(x, y);
		graphics->EndDraw();
		// Render
	}
	}
	delete graphics; // explictly delete graphics since its allocated in heap memory
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	else if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_UP)
		{
			yDisplacement = -speed;
		}
		else if (wParam == VK_DOWN) {
			yDisplacement = speed;
		}
		else if (wParam == VK_LEFT) {
			xDisplacement = -speed;
		}
		else if (wParam == VK_RIGHT) {
			xDisplacement = speed;
		}
	}
	else if (uMsg == WM_KEYUP)
	{
		if (wParam == VK_UP)
		{
			yDisplacement = 0;
		}
		else if (wParam == VK_DOWN) {
			yDisplacement = 0;
		}
		else if (wParam == VK_RIGHT) {
			xDisplacement = 0;
		}
		else if (wParam == VK_LEFT) {
			xDisplacement = 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}