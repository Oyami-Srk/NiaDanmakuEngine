#include "SimpleWindow.h"
#include <map>
#include <stdexcept>

std::map<HWND, SimpleWindow*> SimpleWindowHandle;

SimpleWindow::SimpleWindow(WINSTR lpszCaption, int Width, int Height, HICON hIcon, bool Show, DWORD CFlag) {
	this->SimpleWindowCreateFlag = CFlag;
	if (!this->SimpleWindowCreateFlag)
		this->SimpleWindowCreateFlag = WS_POPUPWINDOW | WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE;
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = lpszCaption;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = hIcon;
	_hInstance = GetModuleHandle(NULL);
	wc.hInstance = _hInstance;
	_Width = Width;
	_Height = Height;
	_ClientX = Width;
	_ClientY = Height;

	RECT rc = { 0, 0,_Width,_Height };
	AdjustWindowRect(&rc, SimpleWindowCreateFlag, NULL);
	_Width = rc.right - rc.left;
	_Height = rc.bottom - rc.top;

	if(RegisterClass(&wc) < 0)
		throw std::runtime_error("Cannot Register Class!");

	_hWnd = CreateWindow(wc.lpszClassName, wc.lpszClassName,
		//WS_POPUPWINDOW | WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE,
		SimpleWindowCreateFlag,
		0, 0, _Width, _Height, NULL, NULL, _hInstance, NULL);

	if (NULL == _hWnd)
		throw std::runtime_error("Cannot Create Window!");
	else
		isRunning = true;

	SimpleWindowHandle[_hWnd] = this;

	UpdateWindow(_hWnd);
	ShowWindow(_hWnd, Show);
}

SimpleWindow::~SimpleWindow() {
	PostQuitMessage(0);
}

LRESULT SimpleWindow::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT SimpleWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto it = SimpleWindowHandle.find(hWnd);
	if (SimpleWindowHandle.end() == it)
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	SimpleWindow* pObj = it->second;

	switch (uMsg) {
	case WM_DESTROY:
		pObj->isRunning = false;
		break;
	default:
		if (pObj != NULL) {
			if (pObj->HandleMessage(hWnd, uMsg, wParam, lParam) == 0)
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		} else {
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	}
	return 0;
}

void SimpleWindow::run(void) {
	MSG msg;
	while (isRunning && GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}