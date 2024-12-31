#include "Camera.h"

/************************************************************************/
/* Base Camera                                                          */
/************************************************************************/

DX11::Camera::Camera()
{
	mNearZ = 0;
	mFarZ = 0;
	mWidth = 0;
	mHeight = 0;
	// world
	mWorld				= XMMatrixIdentity();
	mWorldPosition		= XMMatrixIdentity();
	mWorldRotation		= XMMatrixIdentity();
	mWorldOffset		= XMMatrixIdentity();
	mWorldTranslation	= XMMatrixIdentity();
	mWorldScalling		= XMMatrixIdentity();
	mTexRotation		= XMMatrixIdentity();
	// view
	mView				= XMMatrixIdentity();
	mCamPosition		= XMVectorSet(0, 0, 0, 0);
	mCamTarget			= XMVectorSet(0, 0, 0, 0);
	mCamUp				= XMVectorSet(0, 1, 0, 0);
	mCamOffset			= XMVectorSet(0, 0, 0, 0);
	mCamTargetOffset	= XMVectorSet(0, 0, 0, 0);
	// projection
	mProjection			= XMMatrixIdentity();
	mZoom = 1.0;
}
// ------world
void DX11::Camera::SetWorldPosition(float x, float y, float z)
{
	this->mWorldPosition = XMMatrixTranslation(x, y, z);
	ComputeWorld();
}
void DX11::Camera::SetWorldOffset(float x, float y, float z, bool directSet)
{
	static XMVECTOR l_offset = XMVectorSet(0, 0, 0, 0);
	if (directSet)
		l_offset = XMVectorSet(x, y, z, 0.0);
	else
		l_offset += XMVectorSet(x, y, z, 0);

	this->mWorldOffset = XMMatrixTranslation(l_offset.m128_f32[0], l_offset.m128_f32[1], l_offset.m128_f32[2]);
	ComputeWorld();
}
void DX11::Camera::SetWorldRotation(XMMATRIX pRotation, bool directSet)
{
	if (directSet)
		mWorldRotation = pRotation;
	else
		mWorldRotation *= pRotation;
}

void DX11::Camera::SetWorldScale(float x, float y, float z, bool directSet)
{
	static XMVECTOR l_scale = XMVectorSet(1, 1, 1, 0);
	if (directSet)
		l_scale = XMVectorSet(x, y, z, 0);
	else
		l_scale += XMVectorSet(x, y, z, 0);

	if (l_scale.m128_f32[0] <= 1.0) { l_scale.m128_f32[0] = 1.0; }
	if (l_scale.m128_f32[1] <= 1.0) { l_scale.m128_f32[1] = 1.0; }
	if (l_scale.m128_f32[2] <= 1.0) { l_scale.m128_f32[2] = 1.0; }
	mWorldScalling = XMMatrixScaling(l_scale.m128_f32[0], l_scale.m128_f32[1], l_scale.m128_f32[2]);
	ComputeWorld();
}

void DX11::Camera::SetTexRotation(XMMATRIX pRotation, bool directSet )
{
	if (directSet)
		mTexRotation = pRotation;
	else
		mTexRotation *= pRotation;
}

// ------camera 
void DX11::Camera::SetCamPosition(float x, float y, float z)
{
	this->mCamPosition = XMVectorSet(x, y, z, 0.f);
	ComputeView();
}
void DX11::Camera::SetCamOffset(float x, float y, float z, bool directSet)
{
	if (directSet)
		this->mCamOffset = XMVectorSet(x, y, z, 0.f);
	else
		this->mCamOffset += XMVectorSet(x, y, z, 0.f);
	ComputeView();
}
void DX11::Camera::SetCamTarget(float x, float y, float z)
{
	this->mCamTarget = XMVectorSet(x, y, z, 0);
	ComputeView();
}
void DX11::Camera::SetCamTargetOffset(float x, float y, float z, bool directSet)
{
	if (directSet)
		this->mCamTargetOffset = XMVectorSet(x, y, z, 0.f);
	else
		this->mCamTargetOffset += XMVectorSet(x, y, z, 0.f);
	ComputeView();
}
void DX11::Camera::SetCamUp(float x, float y, float z)
{
	this->mCamUp = XMVectorSet(x, y, z, 0);
	ComputeView();
}

// ------projection
void DX11::Camera::SetProjection(int width, int height, float nearZ, float farZ)
{
	this->mWidth = static_cast<float>(width);
	this->mHeight = static_cast<float>(height);
	this->mNearZ = nearZ;
	this->mFarZ = farZ;
	ComputeProjection();
}	

void DX11::Camera::SetProjection(float l, float r, float b, float t, float nearZ, float farZ)
{
	this->mNearZ = nearZ;
	this->mFarZ = farZ;

	//Compute Projection
	XMMATRIX l_Projection = XMMatrixPerspectiveOffCenterLH(l, r, b, t, mNearZ, mFarZ);
	mProjection = (l_Projection);
}
void DX11::Camera::Zoom(float val)
{
	mZoom += val;
	if (mZoom <= 0.1f)
		mZoom = 0.1f;
	ComputeProjection();
}
//////////////////////////////////////////////////////////////////////////
void DX11::Camera::ComputeWorld()
{
	mWorld = mWorldPosition * mWorldOffset * mWorldScalling;
}

void DX11::Camera::ComputeView()
{
	mView = (XMMatrixLookAtLH(mCamPosition + mCamOffset, mCamTarget + mCamTargetOffset, mCamUp));
}

void DX11::Camera::ComputeProjection()
{
	float l_ZeroArray[16] = { 0 };
	XMMATRIX l_Projection = XMMATRIX(l_ZeroArray);

	
	float ratio = (mWidth / mHeight) * mZoom;
	float l = -ratio;
	float r = ratio ;
	float t = 1.0f * mZoom;
	float b = -1.0f * mZoom;
#if defined (_XM_NO_INTRINSICS_)
	
	l_Projection._11 = float(2 * mNearZ / (r - l));
	l_Projection._22 = float(2 * mNearZ / (t - b));
	l_Projection._31 = float((l + r) / (l - r));
	l_Projection._32 = float((t + b) / (b - t));
	l_Projection._33 = float(mFarZ / (mFarZ - mNearZ));
	l_Projection._34 = float(1.0);
	l_Projection._43 = float(mNearZ * mFarZ / (mNearZ - mFarZ));
#else
	l_Projection.r[0].m128_f32[0] = float(2 * mNearZ / (r - l));
	l_Projection.r[1].m128_f32[1] = float(2 * mNearZ / (t - b));
	l_Projection.r[2].m128_f32[0] = float((l + r) / (l - r));
	l_Projection.r[2].m128_f32[1] = float((t + b) / (b - t));
	l_Projection.r[2].m128_f32[2] = float(mFarZ / (mFarZ - mNearZ));
	l_Projection.r[2].m128_f32[3] = float(1.0);
	l_Projection.r[3].m128_f32[2] = float(mNearZ * mFarZ / (mNearZ - mFarZ));
#endif
	//same thing
	//l_Projection = XMMatrixPerspectiveOffCenterLH(l, r, b, t, mNearZ, mFarZ);
	
	mProjection = (l_Projection);
}

//////////////////////////////////////////////////////////////////////////
const XMMATRIX DX11::Camera::GetWorld()
{
	return (mWorld);
}

const XMMATRIX DX11::Camera::GetView()
{
	return (mView);
}

const XMMATRIX DX11::Camera::GetProjection()
{
	return (mProjection);
}
const XMMATRIX DX11::Camera::GetRotation()
{
	return (mWorldRotation);
}
const XMMATRIX DX11::Camera::GetTranslation()
{
	return (mWorldTranslation);
}

const XMMATRIX DX11::Camera::GetTexRotation()
{
	return (mTexRotation);
}

const XMMATRIX DX11::Camera::GetWorld_t()
{
	return XMMatrixTranspose(mWorld);
}

const XMMATRIX DX11::Camera::GetView_t()
{
	return XMMatrixTranspose(mView);
}

const XMMATRIX DX11::Camera::GetProjection_t()
{
	return XMMatrixTranspose(mProjection);
}
const XMMATRIX DX11::Camera::GetRotation_t()
{
	return XMMatrixTranspose(mWorldRotation);
}
const XMMATRIX DX11::Camera::GetTranslation_t()
{
	return XMMatrixTranspose(mWorldTranslation);
}

const XMMATRIX DX11::Camera::GetTexRotation_t()
{
	return XMMatrixTranspose(mTexRotation);
}