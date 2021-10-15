#ifndef UNICODE
#define UNICODE
#endif 
#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))
#define IS_KEY_PRESSED(key)						(1 << 15) & GetAsyncKeyState(key)

#include "Graphics.h"
#include "Player.h"

Graphics* graphics; // The Almighty gfx
Player player;
FLOAT speed = 10;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void GetKeyUpdates();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

#pragma region WindowSetup



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
#pragma endregion

	player.Init(hwnd);

	// Run the message loop.
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		// If there is a message, then handle the message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&msg); }
		GetKeyUpdates();
		// Update
		graphics->BeginDraw();
		graphics->ClearScreen(0, 0, 0);
		player.Update(graphics);
		graphics->EndDraw();
		// Render
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
	else if (uMsg == WM_MOUSEMOVE)
	{
		player.xAim = GET_X_LPARAM(lParam);
		player.yAim = GET_Y_LPARAM(lParam);
	}
	else if (uMsg == WM_KEYUP)
	{
		if (wParam == VK_UP || wParam == 0x57) { player.ySpeed = 0; }
		if (wParam == VK_DOWN || wParam == 0x53) { player.ySpeed = 0; }
		if (wParam == VK_RIGHT || wParam == 0x44) { player.xSpeed = 0; }
		if (wParam == VK_LEFT || wParam == 0x41) { player.xSpeed = 0; }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void GetKeyUpdates() {

	player.ySpeed = 0;
	player.xSpeed = 0;

	// W => 0x57
	if (IS_KEY_PRESSED(VK_UP) || IS_KEY_PRESSED(0x57)) { player.ySpeed += -speed; }

	// S => 0x53
	if (IS_KEY_PRESSED(VK_DOWN) || IS_KEY_PRESSED(0x53)) { player.ySpeed += speed; }

	// A => 0x41
	if (IS_KEY_PRESSED(VK_LEFT) || IS_KEY_PRESSED(0x41)) { player.xSpeed += -speed; }

	// D => 0x44
	if (IS_KEY_PRESSED(VK_RIGHT) || IS_KEY_PRESSED(0x44)) { player.xSpeed += speed; }
}
