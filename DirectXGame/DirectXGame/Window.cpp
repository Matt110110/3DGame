#include "Window.h"

Window * window = nullptr;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE: // Events fired when the window is created
	{
		window->onCreate();
		break;
	}
	case WM_DESTROY: // Events fired when the window is destroyed
	{
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}

void Window::onDestroy()
{
	m_is_run = false;
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->onUpdate();

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WinProc;

	if (!::RegisterClassEx(&wc)) // If registration of the class fails then we return false
	{
		return false;
	}

	if (!window)
	{
		window = this;
	}

	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);

	if (!m_hwnd) // If the creation fails return 0
	{
		return false;
	}

	// Show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	
	// Flag set true to indicate that the windows is initialized and running
	m_is_run = true;
	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd))
	{
		return false;
	}
	return true;
}

Window::Window()
{
}


Window::~Window()
{
}
