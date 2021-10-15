#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Graphics.h"

Graphics* graphics; // The Almighty gfx

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void GetKeyUpdates();

int IsKeyPressed(int key);

FLOAT x = 200, y = 200;
FLOAT xSpeed = 0;
FLOAT ySpeed = 0;
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
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&msg); }
		else
		{
			GetKeyUpdates();
			// Update
			graphics->BeginDraw();
			graphics->ClearScreen(0, 0, 0);
			{
				if (x > rcWind.right) { x = 0; }
				if (y > rcWind.bottom) { y = 0; }
				if (x < 0) { x = rcWind.right; }
				if (y < 0) { y = rcWind.bottom; }
			}
			x += xSpeed;
			y += ySpeed;
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
	else if (uMsg == WM_KEYUP)
	{
		if (wParam == VK_UP || wParam == 0x57) {
			ySpeed = 0;
		}
		if (wParam == VK_DOWN || wParam == 0x53) {
			ySpeed = 0;
		}
		if (wParam == VK_RIGHT || wParam == 0x44) {
			xSpeed = 0;
		}
		if (wParam == VK_LEFT || wParam == 0x41) {
			xSpeed = 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void GetKeyUpdates() {

	ySpeed = 0;
	xSpeed = 0;
	// W => 0x57
	if (IsKeyPressed(VK_UP) || IsKeyPressed(0x57)) { ySpeed += -speed; }

	// S => 0x53
	if (IsKeyPressed(VK_DOWN) || IsKeyPressed(0x53)) { ySpeed += speed; }

	// A => 0x41
	if (IsKeyPressed(VK_LEFT) || IsKeyPressed(0x41)) { xSpeed += -speed; }

	// D => 0x44
	if (IsKeyPressed(VK_RIGHT) || IsKeyPressed(0x44)) { xSpeed += speed; }
}

int IsKeyPressed(int key)
{
	return (1 << 15) & GetAsyncKeyState(key);
}
