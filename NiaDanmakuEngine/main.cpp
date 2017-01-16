#include "NiaDE/NiaDE.h"

using namespace NiaDE;
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  

class Game : public GameA {
public:
	void OnBackground(float dt) {
		Target->BeginDraw();
		//Target->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		spr->Draw(0, 0, &D2D1::RectF(0, 0, 64, 960));
		Target->EndDraw();
	}

	void OnGameLogic(float dt) {

	}

	X2D::Sprite2D *spr;

	void OnGameInit() {
		spr = new X2D::Sprite2D(Target, L"front00.png",640,480);
	}
};

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	NiaDE::Frame Frame(TEXT("NiaDE"),640,480);
	Frame.registerGameClass(new Game);
	Frame.run();
	return 0;
}