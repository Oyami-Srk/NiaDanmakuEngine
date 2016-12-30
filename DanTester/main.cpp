#include "SimpleWindow/SimpleWindow.h"
#include <d2d1.h>
#include <stdexcept>
#include <vector>
#include "Danmaku/Hops.h"
#pragma comment(lib,"D2d1.lib")

//==Def Windows Class

template <class T> void SafeRelease(T **ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

typedef struct {
	Vector Speed;
	Vector SpeedInc;
	float RotationInc;
	float FramesDelay;
}BalletDescriber;

class BaseBallet {
public:
	BaseBallet(std::vector<BalletDescriber> _anim, Vector _Position = Vector(0, 0)) {
		Position = _Position;
		Anim = _anim;
	}

	BaseBallet(Vector Speed, Vector Rotation, Vector SpeedInc, float RotationInc, Vector _Position = Vector(0, 0)) {
		Position = _Position;
		Anim.push_back({ Speed,SpeedInc,RotationInc});
	}
	
	Vector GetPosition() {
		if (Anim.size() <= 0)
			return Vector(0, 0);
		else if (Anim.size() == 1) {
			Position += (Anim[0].Speed);
			Anim[0].Speed + (Anim[0].SpeedInc.Rotate(Anim[0].RotationInc));
		}
	}

	bool CheckOutside(float Width, float Height, float R) {
		if (Position.X > (Width + R) || Position.Y > (Height + R))
			return (isDestoryed = true);
	}

protected:
	std::vector<BalletDescriber> Anim;
	Vector Position = Vector(0, 0);
	bool isDestoryed = false;
	int nCount = 0;
};


class DanmakuTester : public SimpleWindow {
public:
	DanmakuTester(WINSTR lpszCaption, int Width = 800, int Height = 600, HICON hIcon = NULL, bool Show = true, DWORD CFlag = NULL)
		:SimpleWindow(lpszCaption, Width, Height, hIcon, Show, CFlag) {
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&this->pD2DFactory
		);
		if (!SUCCEEDED(hr))
			throw std::runtime_error("Cannot Create The D2D Factory!");
		hr = pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				this->_hWnd,
				D2D1::SizeU(
					this->_ClientX,
					this->_ClientY
				)
			),
			&this->pTg
		);
		if (!SUCCEEDED(hr))
			throw std::runtime_error("Cannot Create The Hwnd Render Target!");
	}

	~DanmakuTester() {
		SafeRelease(&pTg);
		SafeRelease(&pD2DFactory);
	}
private:
	ID2D1Factory *pD2DFactory = nullptr;
	ID2D1HwndRenderTarget *pTg = nullptr;

};

//==End Def


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DanmakuTester Window(TEXT("Danmaku Tester"));
	Window.run();
	return 0;
}