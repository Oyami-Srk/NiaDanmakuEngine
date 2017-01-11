#ifndef __NIADE_FRAME_H__
#define __NIADE_FRAME_H__

#include "NiaDE.h"
#include "../SimpleWindow/SimpleWindow.h"

namespace NiaDE {
	class Frame :public SimpleWindow {
	public:
		Frame(WINSTR lpszCaption, int Width = 800, int Height = 600, HICON hIcon = NULL, bool Show = true, DWORD CFlag = NULL);
		~Frame();

		virtual void Update(float dt) {};

		virtual void Render(float dt) {};
		
		virtual void InitGame(void) {};

		void run(void);

	private:
		ID2D1Factory *pD2DFactory = nullptr;
		ID2D1HwndRenderTarget *pTg = nullptr;
		bool isFpsLimited = true;
		bool isFpsDisplayed = true;
		float Fps_Limit_Count = 60.0f;
	};
}

#endif