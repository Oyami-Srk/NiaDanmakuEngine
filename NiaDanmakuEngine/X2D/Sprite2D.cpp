#include "Sprite2D.h"

namespace X2D {
	HRESULT Sprite2D::LoadBitmapFromFile(
		ID2D1RenderTarget *pRenderTarget,
		PCWSTR uri,
		ID2D1Bitmap **ppBitmap,
		UINT destinationWidth,
		UINT destinationHeight
	) {
		HRESULT hr = S_OK;

		IWICBitmapDecoder *pDecoder = NULL;
		IWICBitmapFrameDecode *pSource = NULL;
		IWICStream *pStream = NULL;
		IWICFormatConverter *pConverter = NULL;
		IWICBitmapScaler *pScaler = NULL;
		IWICImagingFactory *pIWICFactory = NULL;

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&pIWICFactory
		);

		hr = pIWICFactory->CreateDecoderFromFilename(
			uri,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
		if (SUCCEEDED(hr)) {

			// Create the initial frame.
			hr = pDecoder->GetFrame(0, &pSource);
		}

		if (SUCCEEDED(hr)) {
			hr = pIWICFactory->CreateFormatConverter(&pConverter);
		}
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		UINT originalWidth, originalHeight;
		if (destinationWidth == 0 || destinationHeight == 0) {
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			destinationHeight = originalHeight;
			destinationWidth = originalWidth;
		}
		if (destinationWidth != 0 || destinationHeight != 0) {
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr)) {
				if (destinationWidth == 0) {
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				} else if (destinationHeight == 0) {
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr)) {
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr)) {
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		if (SUCCEEDED(hr)) {
			// Create a Direct2D bitmap from the WIC bitmap.
			hr = pRenderTarget->CreateBitmapFromWicBitmap(
				pConverter,
				NULL,
				ppBitmap
			);
		}
		return hr;
	}

	Sprite2D::Sprite2D(ID2D1RenderTarget *pRenderTarget, PCWSTR uri, int w, int h) {
		this->Target = pRenderTarget;
		if (uri)
			LoadSprite(uri, w, h);
	}

	Sprite2D::Sprite2D(ID2D1RenderTarget *pRenderTarget, ID2D1Bitmap *Bitmap)
		: Target(pRenderTarget), SpriteImage(Bitmap) {

	}

	Sprite2D::~Sprite2D() {
		SAFE_RELEASE(SpriteImage);
	}

	HRESULT Sprite2D::LoadSprite(PCWSTR uri,int w, int h) {
		HRESULT hr = S_FALSE;
 		if (SpriteImage)
 			SpriteImage->Release();
		hr = LoadBitmapFromFile(Target, uri, &SpriteImage, w, h);
		if (hr != S_OK)
			SpriteImage = nullptr;
		else
			Size = SpriteImage->GetSize();
		return hr;
	}
	D2D1_SIZE_F Sprite2D::GetSize() {
		return Size;
	}
	void Sprite2D::Draw(float X, float Y, const D2D1_RECT_F * sourceRectangle, float opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode) {
		if (SpriteImage)
			Target->DrawBitmap(
				SpriteImage,
				D2D1::RectF(X, Y, X + Size.width, Y + Size.height), opacity, interpolationMode, sourceRectangle);
	}
}