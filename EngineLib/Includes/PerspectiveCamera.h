#pragma once

#include "Vector3.h"
#include "Matrix.h"


namespace GT
{
	class Vector3;

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float i_fAspectRatio, float i_fGradFovY, const Vector3& i_oPos, const Vector3& i_oLookAt, const Vector3& i_oUp);
		virtual ~PerspectiveCamera();

	public:
		void SetPos(const Vector3& i_oCameraPos);
		void SetLookAt(const Vector3& i_oLookAt);
		void SetUp(const Vector3& i_oUp);

		const Matrix& GetProjection();
		const Matrix& GetView();

	private:
		float m_fAspectRatio;
		float m_fFovY;

		Vector3 m_oPos;
		Vector3 m_oLookAt;
		Vector3 m_oUp;

		Matrix m_oProjection;
		Matrix m_oView;
	};
}

