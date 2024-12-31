#ifndef _PICK_H__
#define _PICK_H__

#include <d3d11.h>
#include "xnamath.h"
#include <vector>

// only support for DirectX 11 

/*

template<typename T>
t example

typedef struct _structname
{
	XMFLOAT3 Normal; //don't care it exists or not
	XMFLOAT3 Pos;    // muse be have it
}structname;

*/

typedef struct _PickData
{
	int FaceIndex;			// index of face intersected
	XMVECTOR V0;			// Triangle vertex 0 position
	XMVECTOR V1;			// Triangle vertex 1 position
	XMVECTOR V2;			// Triangle vertex 2 position
	float U;                // Barycentric Hit Coordinates    
	float V;                // Barycentric Hit Coordinates
	float Dist;             // Ray-Intersection Parameter Distance
	XMVECTOR PickRayDir;	// Ray direction
	XMVECTOR PickRayOrig;	// Ray origin
							// get vertex average x y z
	float getVtexAvgX() { return (V0.m128_f32[0] + V1.m128_f32[0] + V2.m128_f32[0]) / 3.0; }
	float getVtexAvgY() { return (V0.m128_f32[1] + V1.m128_f32[1] + V2.m128_f32[1]) / 3.0; }
	float getVtexAvgZ() { return (V0.m128_f32[2] + V1.m128_f32[2] + V2.m128_f32[2]) / 3.0; }
	_PickData() { ZeroMemory(this, sizeof(_PickData)); }

	_PickData &operator= (_PickData &in) { memcpy(this, &in, sizeof(_PickData)); return *this; }

}PickData;

//////////////////////////////////////////////////////////////////////////
typedef struct _PickScreenPos
{
	float x;
	float y;
	_PickScreenPos() { ZeroMemory(this, sizeof(_PickScreenPos)); }
	_PickScreenPos(float _x, float _y):x(_x), y(_y){}
	_PickScreenPos &operator= (_PickScreenPos &in) { memcpy(this, &in, sizeof(_PickScreenPos)); return *this; }
}PickScreenPos;

typedef struct _PickViewPort
{
	union 
	{
		struct 
		{
			float x;
			float y;
			float w;
			float h;
		};
		float f[4];
	};
	_PickViewPort() { ZeroMemory(this, sizeof(_PickViewPort)); }
	_PickViewPort(float _x, float _y, float _w, float _h) :x(_x), y(_y), w(_w), h(_h) {}
	_PickViewPort &operator= (_PickViewPort &in) { memcpy(this, &in, sizeof(_PickViewPort)); return *this; }
}PickViewPort;

typedef struct _PickRTV // Render Target View
{
	float w;
	float h;
	_PickRTV() { ZeroMemory(this, sizeof(_PickRTV)); }
	_PickRTV(float _w, float _h) :w(_w), h(_h) {}
	_PickRTV &operator= (_PickRTV &in) { memcpy(this, &in, sizeof(_PickRTV)); return *this; }
}PickRTV;

typedef struct _PickRTW // Render Target Window
{
	float w;
	float h;
	_PickRTW() { ZeroMemory(this, sizeof(_PickRTW)); }
	_PickRTW(float _w, float _h) :w(_w), h(_h) {}
	_PickRTW &operator= (_PickRTW &in) { memcpy(this, &in, sizeof(_PickRTW)); return *this; }
}PickRTW;

typedef struct _PickInput
{
	PickScreenPos	SCpos;
	PickViewPort	VP;
	PickRTV			RTV;
	PickRTW			RTW;
	_PickInput(PickScreenPos _SCpos, PickViewPort _VP, PickRTV _RTV, PickRTW _RTW):
		SCpos(_SCpos), VP(_VP), RTV(_RTV), RTW(_RTW)
	{
	}
	_PickInput() { ZeroMemory(this, sizeof(_PickInput)); }
	_PickInput &operator= (_PickInput &in) { memcpy(this, &in, sizeof(_PickInput)); return *this; }
}PickInput;

class Pick
{
private:
	PickInput mIn;
	float mViewPortPosX;
	float mViewPortPosY;
	float mViewPortW;
	float mViewPortH;

	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;

	PickData mPickData;

public:
	void initialize(PickInput pIn ,XMMATRIX pWorld,XMMATRIX pView,XMMATRIX pProjection)
	{
		// mViewPortPosX = screen posX * (RTV_w / RTW_w) - viewprotx
		// mViewPortPosY = screen posY * (RTV_h / RTW_h) - viewprotx
		// mViewPortW = ScreenW = viewportW
		// mViewPortH = ScreenH = viewportH

		mIn = pIn;
		// transform screen coordinate to view port coordinate
		mViewPortPosX = (mIn.SCpos.x * (mIn.RTV.w / mIn.RTW.w)) - mIn.VP.x;
		mViewPortPosY = (mIn.SCpos.y *(mIn.RTV.h / mIn.RTW.h)) - mIn.VP.y;
		mViewPortW = mIn.VP.w;
		mViewPortH = mIn.VP.h;

		mWorld = pWorld;
		mView = pView;
		mProjection = pProjection;
	}


	template<typename T>
	PickData HitTriNearByVertexs(int pTriangles, T* pVertexBuff)
	{
		CalculatePickRay();

		T *VertexBuf = pVertexBuff;

		auto l_GetVPos = [&](int pWhichTrian, int WhichVertex) //->XMVECTOR
		{
			int idx = (pWhichTrian * 3) + WhichVertex;
			return XMVectorSet(
				VertexBuf[idx].Pos.x,  
				VertexBuf[idx].Pos.y,
				VertexBuf[idx].Pos.z,
				0.0f);
		};

		float preHitdist = 9999999.0;
		XMVECTOR V0, V1, V2;
		float fBary1, fBary2, dist;
		int face = 0;

		for (int i = 0; i < pTriangles; i++)
		{
			V0 = l_GetVPos(i, 0);
			V1 = l_GetVPos(i, 1);
			V2 = l_GetVPos(i, 2);

			// if hit triangle 
			if (IntersectTriangle(mPickData.PickRayOrig, mPickData.PickRayDir, V0, V1, V2, &dist, &fBary1, &fBary2))
			{
				if (dist < preHitdist)
				{
					mPickData.V0 = V0;
					mPickData.V1 = V1;
					mPickData.V2 = V2;
					mPickData.Dist = dist;
					mPickData.FaceIndex = i;
					mPickData.U = fBary1;
					mPickData.V = fBary2;

					preHitdist = dist;
					face = i;
				}
			}
		} //for (int i = 0; i < pTriangles; i++)

		if (face != 0)
			return mPickData;
		else
			return PickData();

	}

	template<typename T1, typename T2>
	PickData HitTriNearByIndices(int pTriangles, T1* pVertexBuff, T2* pIndexBuff)
	{
		CalculatePickRay();
		T1 *VertexBuf = pVertexBuff;
		T2 *IndexBuf = pIndexBuff;

		auto l_GetVPos = [&](int pWhichTrian, int WhichVertex) ->XMVECTOR
		{
			int idx = IndexBuf[(pWhichTrian * 3) + WhichVertex];
			return XMVectorSet(
				VertexBuf[idx].Pos.x,
				VertexBuf[idx].Pos.y,
				VertexBuf[idx].Pos.z,
				0.0f);
		};


		float preHitdist = 9999999.0;
		XMVECTOR V0, V1, V2;
		float fBary1, fBary2, dist;
		int face = 0;

		for (int i = 0; i < pTriangles; i++)
		{
			V0 = l_GetVPos(i, 0);
			V1 = l_GetVPos(i, 1);
			V2 = l_GetVPos(i, 2);

			// if hit triangle 
			if (IntersectTriangle(mPickData.PickRayOrig, mPickData.PickRayDir, V0, V1, V2, &dist, &fBary1, &fBary2))
			{
				if (dist < preHitdist)
				{
					mPickData.V0 = V0;
					mPickData.V1 = V1;
					mPickData.V2 = V2;
					mPickData.Dist = dist;
					mPickData.FaceIndex = i;
					mPickData.U = fBary1;
					mPickData.V = fBary2;

					preHitdist = dist;
					face = i;
				}
			}
		} //for (int i = 0; i < pTriangles; i++)

		if (face != 0)
			return mPickData;
		else
			return PickData();

	}

	template<typename T>
	std::vector<PickData> HitTriAllByVertexs(int pTriangles, T* pVertexBuff)
	{
		CalculatePickRay();

		T *VertexBuf = pVertexBuff;

		auto l_GetVPos = [&](int pWhichTrian, int WhichVertex) //->XMVECTOR
		{
			int idx = (pWhichTrian * 3) + WhichVertex;
			return XMVectorSet(
				VertexBuf[idx].Pos.x,
				VertexBuf[idx].Pos.y,
				VertexBuf[idx].Pos.z,
				0.0f);
		};

		XMVECTOR V0, V1, V2;
		float fBary1, fBary2, dist;
		std::vector<PickData> l_list;
		for (int i = 0; i < pTriangles; i++)
		{
			V0 = l_GetVPos(i, 0);
			V1 = l_GetVPos(i, 1);
			V2 = l_GetVPos(i, 2);

			// if hit triangle 
			if (IntersectTriangle(mPickData.PickRayOrig, mPickData.PickRayDir, V0, V1, V2, &dist, &fBary1, &fBary2))
			{
				mPickData.V0 = V0;
				mPickData.V1 = V1;
				mPickData.V2 = V2;
				mPickData.Dist = dist;
				mPickData.FaceIndex = i;
				mPickData.U = fBary1;
				mPickData.V = fBary2;

				l_list.emplace_back(mPickData);
			}
		}
		return l_list;
	}

	template<typename T1, typename T2>
	std::vector<PickData> HitTriAllByIndices(int pTriangles, T1* pVertexBuff, T2* pIndexBuff)
	{
		CalculatePickRay();
		T1 *VertexBuf = pVertexBuff;
		T2 *IndexBuf = pIndexBuff;

		auto l_GetVPos = [&](int pWhichTrian, int WhichVertex) ->XMVECTOR
		{
			int idx = IndexBuf[(pWhichTrian * 3) + WhichVertex];
			return XMVectorSet(
				VertexBuf[idx].Pos.x,
				VertexBuf[idx].Pos.y,
				VertexBuf[idx].Pos.z,
				0.0f);
		};

		XMVECTOR V0, V1, V2;
		float fBary1, fBary2, dist;
		std::vector<PickData> l_list;
		for (int i = 0; i < pTriangles; i++)
		{
			V0 = l_GetVPos(i, 0);
			V1 = l_GetVPos(i, 1);
			V2 = l_GetVPos(i, 2);

			// if hit triangle 
			if (IntersectTriangle(mPickData.PickRayOrig, mPickData.PickRayDir, V0, V1, V2, &dist, &fBary1, &fBary2))
			{
				mPickData.V0 = V0;
				mPickData.V1 = V1;
				mPickData.V2 = V2;
				mPickData.Dist = dist;
				mPickData.FaceIndex = i;
				mPickData.U = fBary1;
				mPickData.V = fBary2;

				l_list.emplace_back(mPickData);
			}
		}

		return l_list;
	}

protected:
	void CalculatePickRay()
	{
		// Screen = Model * World * View * Projection
		// Screen * INV(Projection) = Model * World * View
		// Screen * INV(Projection) * INV(World * View) = Model

		// Compute the vector of the pick ray in screen space
		XMVECTOR v;
		XMVECTOR v2; // 0~1 to -1 ~ 1
		v2.m128_f32[0] = (((2.0f * (mViewPortPosX)) / mViewPortW) - 1.0);
		v2.m128_f32[1] = -(((2.0f * (mViewPortPosY)) / mViewPortH) - 1.0);
		v2.m128_f32[2] = 1.0f;
		v2.m128_f32[3] = 1.0f;

		XMMATRIX m2;
		XMVECTOR determine2;
		m2 = XMMatrixInverse(&determine2, mProjection);
		v.m128_f32[0] = v2.m128_f32[0] * m2._11 + v2.m128_f32[1] * m2._21 + v2.m128_f32[2] * m2._31 + v2.m128_f32[3] * m2._41;
		v.m128_f32[1] = v2.m128_f32[0] * m2._12 + v2.m128_f32[1] * m2._22 + v2.m128_f32[2] * m2._32 + v2.m128_f32[3] * m2._42;
		v.m128_f32[2] = v2.m128_f32[0] * m2._13 + v2.m128_f32[1] * m2._23 + v2.m128_f32[2] * m2._33 + v2.m128_f32[3] * m2._43;
		v.m128_f32[3] = 1.0;

		// Get the inverse view matrix
		XMMATRIX mWorldView = mWorld * mView;
		XMMATRIX m;
		XMVECTOR determine;
		m = XMMatrixInverse(&determine, mWorldView);

		XMVECTOR vPickRayDir;
		XMVECTOR vPickRayOrig;

		// Transform the screen space pick ray into 3D space
		vPickRayDir.m128_f32[0] = v.m128_f32[0] * m._11 + v.m128_f32[1] * m._21 + v.m128_f32[2] * m._31;
		vPickRayDir.m128_f32[1] = v.m128_f32[0] * m._12 + v.m128_f32[1] * m._22 + v.m128_f32[2] * m._32;
		vPickRayDir.m128_f32[2] = v.m128_f32[0] * m._13 + v.m128_f32[1] * m._23 + v.m128_f32[2] * m._33;
		vPickRayOrig.m128_f32[0] = m._41;
		vPickRayOrig.m128_f32[1] = m._42;
		vPickRayOrig.m128_f32[2] = m._43;

		mPickData.PickRayDir = vPickRayDir;
		mPickData.PickRayDir.m128_f32[3] = 0.0;
		mPickData.PickRayOrig = vPickRayOrig;
		mPickData.PickRayOrig.m128_f32[3] = 0.0;

		//same thing 

		/*float l_x = mIn.SCpos.x * (mIn.RTV.w / mIn.RTW.w);
		float l_y = mIn.SCpos.y * (mIn.RTV.h / mIn.RTW.h);
		XMVECTOR MouseClickNear = XMVectorSet(l_x, l_y, 0.0, 1.0);
		XMVECTOR MouseClickFar = XMVectorSet(l_x, l_y, 1.0, 1.0);
		XMVECTOR NearPos = XMVector3Unproject(MouseClickNear, mIn.VP.x, mIn.VP.y, mIn.VP.w, mIn.VP.h, 0.0, 1.0, mProjection, mView, mWorld);
		XMVECTOR FarPos  = XMVector3Unproject(MouseClickFar , mIn.VP.x, mIn.VP.y, mIn.VP.w, mIn.VP.h, 0.0, 1.0, mProjection, mView, mWorld);
		XMVECTOR dir = XMVector3Normalize(FarPos - NearPos);
		mPickData.PickRayDir = dir;
		mPickData.PickRayOrig = NearPos;*/
	}

	bool IntersectTriangle(const XMVECTOR &orig, const XMVECTOR& dir,
		XMVECTOR& v0, XMVECTOR& v1, XMVECTOR& v2,
		float *dist, float* u, float* v)
	{
		// Find vectors for two edges sharing vert0
		XMVECTOR edge1 = v1 - v0;
		XMVECTOR edge2 = v2 - v0;

		// Begin calculating determinant - also used to calculate U parameter
		XMVECTOR pvec;
		pvec = XMVector3Cross(dir, edge2);

		// If determinant is near zero, ray lies in plane of triangle

		XMVECTOR docVec = XMVector3Dot(edge1, pvec);
		float det = docVec.m128_f32[0] + docVec.m128_f32[1] + docVec.m128_f32[2];

		XMVECTOR tvec;
		if (det > 0)
		{
			tvec = orig - v0;
		}
		else
		{
			tvec = v0 - orig;
			det = -det;
		}

		if (det < 0.0001f)
			return FALSE;

		// Calculate U parameter and test bounds
		docVec = XMVector3Dot(tvec, pvec);
		*u = docVec.m128_f32[0] + docVec.m128_f32[1] + docVec.m128_f32[2];
		if (*u < 0.0f || *u > det)
			return FALSE;

		// Prepare to test V parameter
		XMVECTOR qvec;
		qvec = XMVector3Cross(tvec, edge1);

		// Calculate V parameter and test bounds
		docVec = XMVector3Dot(dir, qvec);
		*v = docVec.m128_f32[0] + docVec.m128_f32[1] + docVec.m128_f32[2];
		if (*v < 0.0f || *u + *v > det)
			return FALSE;

		// Calculate t, scale parameters, ray intersects triangle
		docVec = XMVector3Dot(edge2, qvec);
		*dist = docVec.m128_f32[0] + docVec.m128_f32[1] + docVec.m128_f32[2];
		FLOAT fInvDet = 1.0f / det;
		*dist *= fInvDet;
		*u *= fInvDet;
		*v *= fInvDet;

		return TRUE;
	}


};

#endif