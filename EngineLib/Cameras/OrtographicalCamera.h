#pragma once

#include "Math\Vector3.h"
#include "Math\Matrix.h"

namespace GT
{
	class OrtographicalCamera
	{
	public:
		OrtographicalCamera(const float i_fWidth, const float i_fHeight, const Vector3& i_oStartPos, const Vector3& i_oStartLookAt, const Vector3& i_oStartUp);
		~OrtographicalCamera();

	public:
		void SetPos(const Vector3& i_oCameraPos);
		void SetLookAt(const Vector3& i_oLookAt);
		void SetUp(const Vector3& i_oUp);

		const Matrix& GetProjection();
		const Matrix& GetView();

	private:
		float m_fWidth;
		float m_fHeight;

		Vector3 m_oPos;
		Vector3 m_oLookAt;
		Vector3 m_oUp;

		Matrix m_oProjection;
		Matrix m_oView;
	};
}
