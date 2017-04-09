#include "SimpleCamera.h"

namespace GT
{
	SimpleCamera::SimpleCamera
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
		m_oProjection = Matrix::Transpose(Matrix::Perspective(m_fFovY, m_fAspectRatio, 0.01f, 1000.0f));
	}

	SimpleCamera::~SimpleCamera()
	{
		//Nothing to do here
	}

	void SimpleCamera::SetLookAt(const Vector3& i_oLookAt)
	{
		m_oLookAt = i_oLookAt;
	}

	void SimpleCamera::SetPos(const Vector3& i_oPos)
	{
		m_oPos = i_oPos;
	}

	void SimpleCamera::SetUp(const Vector3& i_oUp)
	{
		m_oUp = i_oUp;
	}

	const Matrix& SimpleCamera::GetProjection()
	{
		return m_oProjection;
	}

	const Matrix& SimpleCamera::GetView()
	{
		m_oView = Matrix::Transpose(Matrix::View(m_oPos, m_oLookAt, m_oUp));
		return m_oView;
	}
}