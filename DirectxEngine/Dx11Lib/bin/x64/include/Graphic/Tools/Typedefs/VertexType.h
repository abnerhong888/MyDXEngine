#ifndef __VERTEXTYPE_H__
#define __VERTEXTYPE_H__

#include <d3d11.h>
#include "DirectXMath.h"
using namespace DirectX;
typedef struct _PlaneVertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
	_PlaneVertex()
	{
		ZeroMemory(this, sizeof(_PlaneVertex));
	}

	_PlaneVertex(XMFLOAT3 _Pos, XMFLOAT2 _Tex): Pos(_Pos), Tex(_Tex)
	{
	}

}PlaneVertex;


#endif