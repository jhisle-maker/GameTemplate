#include "PerspectiveCamera.h"

namespace GT
{
	PerspectiveCamera::PerspectiveCamera
	(
		float i_fAspectRatio, 
		float i_fGradFovY, 
		const Vector3& i_oPos, 
		const Vector3& i_oLookAt, 
		const Vector3& i_oUp
	)
		: m_fAspectRatio(i_fAspectRatio)
		, m_fFovY(DirectX::XMConvertToRadians(i_fGradFovY))
		, m_oPos(i_oPos)
		, m_oLookAt(i_oLookAt)
		, m_oUp(i_oUp)
		, m_oProjection(Matrix::Identity)
		, m_oView(Matrix::Identity)
	{
		m_oProjection = Matrix::Perspective(m_fFovY, m_fAspectRatio, 0.01f, 1000.0f);
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
		//Nothing to do here
	}

	void PerspectiveCamera::SetLookAt(const Vector3& i_oLookAt)
	{
		m_oLookAt = i_oLookAt;
	}

	void PerspectiveCamera::SetPos(const Vector3& i_oPos)
	{
		m_oPos = i_oPos;
	}

	void PerspectiveCamera::SetUp(const Vector3& i_oUp)
	{
		m_oUp = i_oUp;
	}

	const Matrix& PerspectiveCamera::GetProjection()
	{
		return m_oProjection;
	}

	const Matrix& PerspectiveCamera::GetView()
	{
		m_oView = Matrix::View(m_oPos, m_oLookAt, m_oUp);
		return m_oView;
	}
}