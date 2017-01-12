#ifndef __NIADE_GAME_H__
#define __NIADE_GAME_H__

#include "NiaDE.h"

namespace NiaDE {
	class GameA {
	public:
		GameA(ID2D1HwndRenderTarget*);

	public:	//Virtual
		virtual void OnBackground(float dt) {};
		virtual void OnLogoArea(float dt) {};
		virtual void OnGameLogic(float dt) {};
		virtual void OnGameArea(float dt) {};
		virtual void OnDataArea(float dt) {};
		virtual void OnGameInit() {};
		virtual void OnGameRelease() {};

	protected:
		ID2D1HwndRenderTarget* Target;
	};
}

#endif