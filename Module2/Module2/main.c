#include <windows.h>

BOOL  IsRunning = TRUE;

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;

	switch (uMsg)
	{
	case WM_KEYUP:
	{
		IsRunning = FALSE;
	}
	break;

	case WM_ACTIVATE:
	case WM_CREATE:
	case WM_DESTROY:
	{
	}
	break;
	
	default:
		Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return Result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = MainWindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "Module 2";

	if (!RegisterClass(&wc))
	{
		// considered bad because it doesn't allow for cleanup and deallocation
		exit(EXIT_FAILURE);
	}

	HWND mainWindow;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r;
	r.top = r.left = 0;
	r.right = 800;
	r.bottom = 600;

	AdjustWindowRect(&r, WindowStyle, FALSE);

	mainWindow = CreateWindowEx(0, "Module 2", "Lesson 2.1", WindowStyle, 
		CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top, 
		NULL, NULL, hInstance, 0);

	ShowWindow(mainWindow, SW_SHOWDEFAULT);

	HDC DeviceContext = GetDC(mainWindow);
	PatBlt(DeviceContext, 0, 0, 800, 600, BLACKNESS);
	ReleaseDC(mainWindow, DeviceContext);
	
	MSG msg;
	while (IsRunning)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return 0;
}