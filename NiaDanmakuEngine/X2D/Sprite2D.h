#ifndef __SPRITE2D_H__
#define __SPRITE2D_H__

#include "X2D.h"

namespace X2D {
	class Sprite2D {
	public:
		static HRESULT LoadBitmapFromFile(
			ID2D1RenderTarget *pRenderTarget,
			PCWSTR uri,
			ID2D1Bitmap **ppBitmap,
			UINT destinationWidth = 0,
			UINT destinationHeight = 0
		);

	public:
		Sprite2D(ID2D1RenderTarget *pRenderTarget, PCWSTR uri = NULL, int w = 0, int h = 0);
		Sprite2D(ID2D1RenderTarget *pRenderTarget, ID2D1Bitmap *Bitmap = NULL);
		~Sprite2D();
		HRESULT LoadSprite(PCWSTR uri, int w = 0, int h = 0);
		D2D1_SIZE_F GetSize();

		void Draw(float X, float Y,
			const D2D1_RECT_F *sourceRectangle = NULL,
			float opacity = 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

	protected:
		ID2D1RenderTarget *Target = nullptr;
		ID2D1Bitmap *SpriteImage = NULL;
		D2D1_SIZE_F Size;
	};
}

#endif