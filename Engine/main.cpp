#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Graphics.h"

Graphics* graphics; // The Almighty gfx

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	//HWND hwnd = CreateWindowEx(
	//	0,				// Optional window styles.
	//	CLASS_NAME,     // Window class
	//	L"Car Game",	// Window text
	//	NULL,			// Window style

	//	// Size and position
	//	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

	//	NULL,       // Parent window    
	//	NULL,       // Menu
	//	hInstance,  // Instance handle
	//	NULL        // Additional application data
	//);

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


	if (hwnd == NULL)	return 0;

	SetWindowLong(hwnd, GWL_STYLE, 0); // Remove all window styles, basically removes the border and close|min|max buttons .. i hate those

	graphics = new Graphics();
	if (!graphics->Init(hwnd))
	{
		delete graphics;
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);

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

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}