#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "..\GraphicCommon.h"

namespace DX11
{
	/************************************************************************/
	/* Base Camera                                                          */
	/************************************************************************/
	class Camera
	{
	public:
		Camera();
		// world
		void SetWorldPosition(float x, float y, float z);
		void SetWorldOffset(float x, float y, float z, bool directSet = false);
		void SetWorldRotation(XMMATRIX pRotation, bool directSet = false);
		void SetWorldScale(float x, float y, float z, bool directSet = false);
		void SetTexRotation(XMMATRIX pRotation, bool directSet = false);
		// view
		void SetCamPosition(float x, float y, float z);
		void SetCamOffset(float x, float y, float z, bool directSet = false);
		void SetCamTarget(float x, float y, float z);
		void SetCamTargetOffset(float x, float y, float z, bool directSet = false);
		void SetCamUp(float x, float y, float z);
		// projection
		void SetProjection(int width, int height, float nearZ, float farZ);
		void SetProjection(float l, float r, float b, float t, float nearZ, float farZ);
		void Zoom(float val);

		const XMMATRIX GetWorld();
		const XMMATRIX GetView();
		const XMMATRIX GetProjection();
		const XMMATRIX GetRotation();
		const XMMATRIX GetTranslation();
		const XMMATRIX GetTexRotation();

		const XMMATRIX GetWorld_t();
		const XMMATRIX GetView_t();
		const XMMATRIX GetProjection_t();
		const XMMATRIX GetRotation_t();
		const XMMATRIX GetTranslation_t();
		const XMMATRIX GetTexRotation_t();

	protected:
		void ComputeWorld();
		void ComputeView();
		void ComputeProjection();
	private:
		float mNearZ;
		float mFarZ;
		float mWidth;
		float mHeight;
		
		//world
		XMMATRIX mWorld;
		XMMATRIX mWorldPosition;
		XMMATRIX mWorldOffset;
		XMMATRIX mWorldRotation;
		XMMATRIX mWorldTranslation;
		XMMATRIX mWorldScalling;
		XMMATRIX mTexRotation;
		// view
		XMMATRIX mView;
		XMVECTOR mCamPosition;
		XMVECTOR mCamOffset;
		XMVECTOR mCamTarget;
		XMVECTOR mCamTargetOffset;
		XMVECTOR mCamUp;
		
		// project
		XMMATRIX mProjection;
		float mZoom;
		
	};
}


#endif