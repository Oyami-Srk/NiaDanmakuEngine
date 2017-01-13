#include "NiaDE/NiaDE.h"
#include <wincodec.h>
#pragma comment(lib,"Windowscodecs.lib")

using namespace NiaDE;
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)  
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)  

class Game : public GameA {
public:
	void OnBackground(float dt) {
		Target->BeginDraw();
		Target->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		DrawBitmap();
		Target->EndDraw();
	}

	void OnGameLogic(float dt) {
		if (KEY_DOWN(VK_SHIFT))
			OutputDebugStringA("ShiftDown!\n");
		if (KEY_UP(VK_SHIFT))
			OutputDebugStringA("ShiftUp!\n");
			
	}

	void DrawBitmap() {
		// Clear background color to dark cyan
		//Target->Clear(D2D1::ColorF(D2D1::ColorF::White));

// 		D2D1_SIZE_F size = pBitmap->GetSize();
// 		D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(10.f, 10.f);
// 		
// 
// 		// Draw bitmap
// 		Target->DrawBitmap(
// 			pBitmap,
// 			D2D1::RectF(
// 				upperLeftCorner.x,
// 				upperLeftCorner.y,
// 				upperLeftCorner.x + size.width,
// 				upperLeftCorner.y + size.height)
// 		);

		Target->FillRectangle(D2D1::RectF(0, 0, 800, 600), pBb);
		Target->DrawRectangle(D2D1::RectF(0, 0, 800, 600), pBb, 1, NULL);
	}

	ID2D1Bitmap *pBitmap;
	ID2D1BitmapBrush *pBb;

	void OnGameInit() {
		IWICImagingFactory *pFactory = NULL;
		IWICBitmapDecoder *pDecoder = NULL;

		HRESULT hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&pFactory
		);

// 		if (SUCCEEDED(hr)) {
// 			hr = pFactory->CreateDecoderFromFilename(
// 				L"bg.png",
// 				NULL,
// 				GENERIC_READ,
// 				WICDecodeMetadataCacheOnDemand,
// 				&pDecoder);
// 		}
// 
// 		if (SUCCEEDED(hr)) {
// 			UINT uiFrameCount = 0;
// 			hr = pDecoder->GetFrameCount(&uiFrameCount);
// 		}

		LoadBitmapFromFile(Target, pFactory, L"bg.png", 50, 50, &pBitmap);
		Target->CreateBitmapBrush(pBitmap, &pBb);
// 
// 		if (pFactory) {
// 			pFactory->Release();
// 		}
// 
// 		if (pDecoder) {
// 			pDecoder->Release();
// 		}

	}

	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap **ppBitmap
	) {
		HRESULT hr = S_OK;

		IWICBitmapDecoder *pDecoder = NULL;
		IWICBitmapFrameDecode *pSource = NULL;
		IWICStream *pStream = NULL;
		IWICFormatConverter *pConverter = NULL;
		IWICBitmapScaler *pScaler = NULL;

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
		if (destinationWidth != 0 || destinationHeight != 0) {
			UINT originalWidth, originalHeight;
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
		return 0;
	}
};

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	NiaDE::Frame Frame(TEXT("NiaDE"));
	Frame.registerGameClass(new Game);
	Frame.run();
	return 0;
}