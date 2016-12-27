#include "SimpleWindow/SimpleWindow.h"

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SimpleWindow Window(TEXT("NiaDE"));
	Window.run();
	return 0;
}