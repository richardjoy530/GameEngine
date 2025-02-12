#ifndef UNICODE
#define UNICODE
#endif

#include "Player.h"
#include "Target.h"
#include <time.h>
#include <string>
#include <chrono>
#include <iostream>


Graphics* graphics; // The Almighty gfx
Player player;
Target target;

std::chrono::time_point<std::chrono::system_clock> m_StartTime;
std::chrono::time_point<std::chrono::system_clock> m_EndTime;

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
		WS_MAXIMIZE, // Fullscreen
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // x, y, width, height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)	return 1;

	SetWindowLong(hwnd, GWL_STYLE, 0); // Remove all window styles, basically removes the border and close|min|max buttons ... I hate those

	graphics = new Graphics();

	if (!graphics->Init(hwnd))
	{
		delete graphics;
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
    ShowCursor(NULL);
#pragma endregion

	// Run the message loop.
	MSG msg;
	msg.message = WM_NULL;
	std::wstring ms = L"0";

	player.Init(hwnd);
	while (msg.message != WM_QUIT)
	{
		m_StartTime = std::chrono::system_clock::now();
		// If there is a message, then handle the message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
		    DispatchMessage(&msg);
		}
		player.Update();
		// target.Update();

		graphics->BeginDraw();
		graphics->ClearScreen(0, 0, 0);
		D2D1_RECT_F rect = { 0, 0, 100, 50 };
		graphics->WriteText(L"FPS: "+ms, rect);
		// target.Render(graphics);
		player.Render(graphics);
		graphics->EndDraw();
		m_EndTime = std::chrono::system_clock::now();

		ms = std::to_wstring(1000/std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime).count());
	}
	delete graphics; // explicitly delete graphics since it's allocated in heap memory
    std::cout << "exit 0";
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
