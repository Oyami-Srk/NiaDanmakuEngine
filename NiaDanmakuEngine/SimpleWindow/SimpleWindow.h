#ifndef __SIMPLEWINDOW_H__
#define __SIMPLEWINDOW_H__
#include <Windows.h>

#ifdef _UNICODE
#define WINSTR LPWSTR
#else
#define WINSTR LPCSTR
#endif 

class SimpleWindow {
public:
	SimpleWindow(WINSTR lpszCaption, int Width = 800, int Height = 600, HICON hIcon = NULL, bool Show = true, DWORD CFlag = NULL);
	~SimpleWindow();
	virtual LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void run(void);
	bool isRunning = false;

protected:
	DWORD SimpleWindowCreateFlag = NULL;
	HINSTANCE _hInstance;
	HWND _hWnd;
	int _Width;
	int _Height;
	int _ClientX;
	int _ClientY;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif