#ifndef __NIADE_GAME_H__
#define __NIADE_GAME_H__

#include "NiaDE.h"

namespace NiaDE {
	typedef struct {
		int keyCode;
	}KeyMsg;

	class GameA {
	public:
		GameA(ID2D1HwndRenderTarget*);
		~GameA();

	public:	//Virtual
		virtual void OnBackground() {};
		virtual void OnLogoArea() {};
		virtual void OnGameLogic() {};
		virtual void OnGameArea() {};
		virtual void OnDataArea() {};
		virtual void OnKeyEvent() {};

	protected:
		ID2D1HwndRenderTarget* Target;
		
	};
}

#endif