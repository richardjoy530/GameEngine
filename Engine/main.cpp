#ifndef UNICODE
#define UNICODE
#endif 

#include "Graphics.h"
#include "Player.h"

Graphics* graphics; // The Almighty gfx
Player player;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
#pragma endregion

	player.Init(hwnd);

	// Run the message loop.
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		// If there is a message, then handle the message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&msg); }

		player.Update();

		graphics->BeginDraw();
		graphics->ClearScreen(0, 0, 0);
		player.Render(graphics);
		graphics->EndDraw();
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
	else { player.OnWinEvent(uMsg, wParam, lParam); }

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
