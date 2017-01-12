#include "NiaDE_Frame.h"

namespace NiaDE {
	Frame::Frame(WINSTR lpszCaption, int Width, int Height, HICON hIcon, bool Show, DWORD CFlag) :
		SimpleWindow(lpszCaption, Width, Height, hIcon, Show, CFlag) {
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

	Frame::~Frame() {
		SafeRelease(&pTg);
		SafeRelease(&pD2DFactory);
	}

	void Frame::run(void) {
		if (!pGame) {
			throw std::runtime_error("Where is Game?");
			return;
		}
		pGame->OnGameInit();
		MSG msg;//��Ϣ�ṹ
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
		QueryPerformanceCounter(&oldCount); // ��ȡ΢�뼶ʱ��

		char FPSbuf[64];

		while (isRunning) {
			//����Windows��Ϣ
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//ִ����Ⱦ
			pGame->OnGameLogic(m_DelayTime);
			pGame->OnBackground(m_DelayTime);
			pGame->OnGameArea(m_DelayTime);
			pGame->OnLogoArea(m_DelayTime);
			pGame->OnDataArea(m_DelayTime);

			m_DelayTime = time(NULL) - m_LastTime;
			if (this->isFpsDisplayed) {
				static int frameCount = 0;
				static LARGE_INTEGER lastTime, curTime;

				frameCount++;
				QueryPerformanceCounter(&curTime);
				float deltaTime = (curTime.QuadPart - lastTime.QuadPart) / fFrequency; // ��λs
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
				while ((deltaCount.QuadPart = count.QuadPart - oldCount.QuadPart) < minDeltaCount.QuadPart) // ����1/60s֮ǰѭ���ȴ�
				{
					if (deltaCount.QuadPart * 1000 / frequency.QuadPart < 15) // ������15ms���ڣ���ֵԽ��ռCPUԽ�٣���̫���˻᲻��ȷ
						Sleep(1); // ��CPU������������
					QueryPerformanceCounter(&count);
				}
				oldCount = count;
			}
			m_LastTime = time(NULL);
		}
	}

	void Frame::registerGameClass(GameA *pG) {
		this->pGame = pG;
	}

}