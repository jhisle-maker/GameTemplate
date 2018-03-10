#include "OrtographicalCamera.h"

namespace GT
{
	OrtographicalCamera::OrtographicalCamera
	(
		float i_fWidth,
		float i_fHeight,
		const Vector3& i_oPos,
		const Vector3& i_oLookAt,
		const Vector3& i_oUp
	)
		: m_fWidth(i_fWidth)
		, m_fHeight(DirectX::XMConvertToRadians(i_fHeight))
		, m_oPos(i_oPos)
		, m_oLookAt(i_oLookAt)
		, m_oUp(i_oUp)
		, m_oProjection(Matrix::Identity)
		, m_oView(Matrix::Identity)
	{
		m_oProjection = Matrix::Ortographic(i_fWidth, i_fHeight, 0.01f, 1000.0f);
	}

	OrtographicalCamera::~OrtographicalCamera()
	{
		//Nothing to do here
	}

	void OrtographicalCamera::SetLookAt(const Vector3& i_oLookAt)
	{
		m_oLookAt = i_oLookAt;
	}

	void OrtographicalCamera::SetPos(const Vector3& i_oPos)
	{
		m_oPos = i_oPos;
	}

	void OrtographicalCamera::SetUp(const Vector3& i_oUp)
	{
		m_oUp = i_oUp;
	}

	const Matrix& OrtographicalCamera::GetProjection()
	{
		return m_oProjection;
	}

	const Matrix& OrtographicalCamera::GetView()
	{
		m_oView = Matrix::View(m_oPos, m_oLookAt, m_oUp);
		return m_oView;
	}
}