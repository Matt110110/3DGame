#pragma once
#include <Windows.h>

class Window
{
protected:
	HWND m_hwnd;
public:
	//EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	bool broadcast();
	bool isRun();

	// Initialize the window
	bool init();
	// Release the window
	bool release();
	bool m_is_run;
	Window();
	~Window();
};

