#include "NiaDE_Game.h"

namespace NiaDE {
	void GameA::RegisterClass(ID2D1HwndRenderTarget * _T) {
		this->Target = _T;
	}
}