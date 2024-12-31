#ifndef __CONSTANTBUFFTYPE_H__
#define __CONSTANTBUFFTYPE_H__

#include <d3d11.h>
#include "DirectXMath.h"
using namespace DirectX;

typedef struct Tex2D_ColorAlphaCB
{
	float r;
	float g;
	float b;
	float Alpha;
	Tex2D_ColorAlphaCB() { ZeroMemory(this, sizeof(Tex2D_ColorAlphaCB)); }
}Tex2D_ColorAlphaCB;

typedef struct Tex2D_ColorRatioAlphaCB
{
	float ColorRatio;
	float Alpha;
	float useless[2];
	Tex2D_ColorRatioAlphaCB() { ZeroMemory(this, sizeof(Tex2D_ColorRatioAlphaCB)); }
}Tex2D_ColorRatioAlphaCB;



#endif