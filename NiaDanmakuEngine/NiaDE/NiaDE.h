#ifndef __NIADE_H__
#define __NIADE_H__
#define NIADE_V 1

#include <d2d1.h>
#include <stdexcept>
#include <vector>
#include <time.h>
#pragma comment(lib,"D2d1.lib")
#pragma comment(lib,"Winmm.lib")

template <class T> void SafeRelease(T **ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

#include "NiaDE_Frame.h"

#endif