#include "NiaDE/NiaDE.h"

using namespace NiaDE;
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  

class Game : public GameA {
public:
	void OnBackground(float dt) {
		Target->BeginDraw();
		Target->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		spr->Draw(0,0);
		Target->EndDraw();
	}

	void OnGameLogic(float dt) {
		if (KEY_DOWN(VK_SHIFT))
			OutputDebugStringA("ShiftDown!\n");
		if (KEY_UP(VK_SHIFT))
			OutputDebugStringA("ShiftUp!\n");
			
	}

	X2D::Sprite2D *spr;

	void OnGameInit() {
// 		X2D::Sprite2D::LoadBitmapFromFile(Target, L"bg.png", 50, 50, &pBitmap);
// 		Target->CreateBitmapBrush(pBitmap, &pBb);
		spr = new X2D::Sprite2D(Target, L"bg.png");
	}
};

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	NiaDE::Frame Frame(TEXT("NiaDE"),640,480);
	Frame.registerGameClass(new Game);
	Frame.run();
	return 0;
}