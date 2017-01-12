#include "NiaDE/NiaDE.h"

using namespace NiaDE;

class Game : public GameA {
	Game(ID2D1HwndRenderTarget *_T) :GameA(_T) {};
};

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	NiaDE::Frame Frame(TEXT("NiaDE"));
	Frame.registerGameClass(Game);
	Frame.run();
	return 0;
}