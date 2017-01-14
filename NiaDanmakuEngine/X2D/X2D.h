#ifndef __X2D_H__
#define __X2D_H__

#include <d2d1.h>
#pragma comment(lib,"D2d1.lib")
#include <wincodec.h>
#pragma comment(lib,"Windowscodecs.lib")

#define SAFE_RELEASE(p) if(p){ p->Release(); p=NULL; }

#include "Sprite2D.h"

#endif