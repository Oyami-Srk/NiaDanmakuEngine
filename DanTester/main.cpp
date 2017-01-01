#include "SimpleWindow/SimpleWindow.h"
#include <d2d1.h>
#include <stdexcept>
#include <vector>
#include "Danmaku/Hops.h"
#include <time.h>
#pragma comment(lib,"D2d1.lib")
#pragma comment(lib,"Winmm.lib")

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
	int FramesDelay;	//setting to -1 means never ends;
}BalletDescriber;

class BaseBallet {
public:
	BaseBallet(std::vector<BalletDescriber> _anim, Vector _Position = Vector(0, 0)) {
		Position = _Position;
		Anim = _anim;
	}

	BaseBallet(Vector _Position = Vector(0, 0), Vector Speed = Vector(0, 0), Vector SpeedInc = Vector(0, 0), float RotationInc = 0.0f, int _Fdelay = 0) {
		Position = _Position;
		Anim.push_back({ Speed,SpeedInc,RotationInc,_Fdelay });
	}

	void PushMov(Vector Speed, Vector SpeedInc, float RotationInc, int _Fdelay) {
		Anim.push_back({ Speed,SpeedInc,RotationInc,_Fdelay });
	}
	
	Vector GetPosition() {
		if (Anim.size() <= 0)
			isDestoryed = true;//TODO: Deal with it!
		else if (Anim.size() == 1)
			_change_Position_by_AnimId(0);
		else {
			int TotalDelay = 0;
			int i = 0;
			bool set = false;
			for (auto v : Anim) {
				TotalDelay += v.FramesDelay;
				if (v.FramesDelay == -1 || nCount <= TotalDelay) {
					_change_Position_by_AnimId(i);
					set = true;
					break;
				}
				i++;
			}
			if (!set)
				isDestoryed = true;
		}
		if (isDestoryed)
			Position = Vector(0, 0);
		nCount++;
		return Position;
	}

	bool CheckOutside(float Width, float Height, float R) {
		if (Position.X > (Width + R) || Position.Y > (Height + R))
			return (isDestoryed = true);
	}

	bool isDestoryed = false;

public:
	std::vector<BalletDescriber> Anim;
	Vector Position = Vector(0, 0);
	int nCount = 0;

private: 
	void _change_Position_by_AnimId(int id) {
		Position += (Anim[id].Speed);
		/*There is a question in sentence below: Rotate the speed first or increase the speed first*/

		
 		Anim[id].Speed += Anim[id].SpeedInc;
 		Anim[id].Speed = Anim[id].Speed.Rotate(Anim[id].RotationInc);
		

		//Anim[id].Speed += (Anim[id].SpeedInc = Anim[id].SpeedInc.Rotate(Anim[id].RotationInc));

		char Buf[32];
		sprintf(Buf, "vX:%f,vY:%f\n", Anim[id].Speed.X, Anim[id].Speed.Y);
		OutputDebugStringA(Buf);
	}
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

	void Update(float dt) {

	}

	void DrawPoint(float x, float y, float r = 2) {
		pTg->FillRectangle(D2D1::RectF(x - r, y - r, x + r, y + r), pBlackBrush);
	}

	void Render(float dt) {
		pTg->BeginDraw();
		pTg->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		Vector v = b->GetPosition();
		DrawPoint(v.X, v.Y);
		pTg->EndDraw();
	}

	BaseBallet *b;
	ID2D1SolidColorBrush* pBlackBrush = NULL;

	void InitGame(void) {
		b = new BaseBallet(Vector(400, 300));
		b->PushMov(Vector(1, 1), Vector(0, 0), 0.0f, -1);
		pTg->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&pBlackBrush
		);
	}

	void run(void) {
		InitGame();
		MSG msg;//消息结构
		bool done, result = true;
		ZeroMemory(&msg, sizeof(MSG));
		done = false;
		double m_LastTime = time(NULL);
		double m_DelayTime = 0;

		LARGE_INTEGER frequency, minDeltaCount, count, oldCount;
		float fFrequency;
		QueryPerformanceFrequency(&frequency);
		fFrequency = (float)frequency.QuadPart;
		minDeltaCount.QuadPart = frequency.QuadPart / Fps_Limit_Count;
		QueryPerformanceCounter(&oldCount); // 获取微秒级时间

		char FPSbuf[64];

		while (isRunning) {
			//处理Windows消息
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//执行渲染
			this->Update(m_DelayTime);
			this->Render(m_DelayTime);
			m_DelayTime = time(NULL) - m_LastTime;
			if (this->isFpsDisplayed) {
				static int frameCount = 0;
				static LARGE_INTEGER lastTime, curTime;

				frameCount++;
				QueryPerformanceCounter(&curTime);
				float deltaTime = (curTime.QuadPart - lastTime.QuadPart) / fFrequency; // 单位s
				if (deltaTime >= 1.0f) {
					float fps = frameCount / deltaTime;
					frameCount = 0;
					sprintf(FPSbuf, "%3.1f", fps);
					SetWindowTextA(this->_hWnd, FPSbuf);
					lastTime = curTime;
				}
			}

			if (this->isFpsLimited) {
				QueryPerformanceCounter(&count);
				LARGE_INTEGER deltaCount;
				while ((deltaCount.QuadPart = count.QuadPart - oldCount.QuadPart) < minDeltaCount.QuadPart) // 经过1/60s之前循环等待
				{
					if (deltaCount.QuadPart * 1000 / frequency.QuadPart < 15) // 经过了15ms以内，数值越大占CPU越少，但太大了会不精确
						Sleep(1); // 把CPU交给其他程序
					QueryPerformanceCounter(&count);
				}
				oldCount = count;
			}
			m_LastTime = time(NULL);
		}
	}

private:
	ID2D1Factory *pD2DFactory = nullptr;
	ID2D1HwndRenderTarget *pTg = nullptr;
	bool isFpsLimited = true;
	bool isFpsDisplayed = true;
	float Fps_Limit_Count = 60.0f;

};

//==End Def


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DanmakuTester Window(TEXT("Danmaku Tester"));
	Window.run();
	return 0;
}