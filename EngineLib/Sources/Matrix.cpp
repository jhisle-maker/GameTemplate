#include "Matrix.h"
#include "Vector3.h"

namespace GT
{
	Matrix::Matrix()
		: m_oInnerMatrix(0.0f, 0.0f, 0.0f, 0.0f, 
						 0.0f, 0.0f, 0.0f, 0.0f, 
						 0.0f, 0.0f, 0.0f, 0.0f, 
						 0.0f, 0.0f, 0.0f, 0.0f)
	{
		//Nothing to do here
	}

	Matrix::Matrix(float i_f00, float i_f01, float i_f02, float i_f03,
				   float i_f10, float i_f11, float i_f12, float i_f13,
				   float i_f20, float i_f21, float i_f22, float i_f23,
				   float i_f30, float i_f31, float i_f32, float i_f33)
		: m_oInnerMatrix(i_f00, i_f01, i_f02, i_f03, i_f10, i_f11, i_f12, i_f13, i_f20, i_f21, i_f22, i_f23, i_f30, i_f31, i_f32, i_f33)
	{
		//Nothing to do here
	}

	Matrix Matrix::Transpose(const Matrix& i_oSource)
	{
		return DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&i_oSource.GetXMData()));
	}

	Matrix Matrix::Perspective(const float i_fFovY, const float i_fAspectRatio, const float i_fNearPlane, const float i_fFarPlane)
	{
		return Transpose(DirectX::XMMatrixPerspectiveFovRH(i_fFovY, i_fAspectRatio, i_fNearPlane, i_fFarPlane));
	}

	Matrix Matrix::Ortographic(const float i_fWidth, const float i_fHeight, const float i_fNearPlane, const float i_fFarPlane)
	{
		return Transpose(DirectX::XMMatrixOrthographicRH(i_fWidth, i_fHeight, i_fNearPlane,  i_fFarPlane));
	}

	Matrix Matrix::RotationX(const float i_fRadians)
	{
		return Transpose(DirectX::XMMatrixRotationX(i_fRadians));
	}

	Matrix Matrix::RotationY(const float i_fRadians)
	{
		return Transpose(DirectX::XMMatrixRotationY(i_fRadians));
	}

	Matrix Matrix::RotationZ(const float i_fRadians)
	{
		return Transpose(DirectX::XMMatrixRotationZ(i_fRadians));
	}

	Matrix Matrix::View(const Vector3& i_oPos, const Vector3& i_oLookAt, const Vector3& i_oUp)
	{
		
		return Transpose(DirectX::XMMatrixLookAtRH
		(
			DirectX::XMLoadFloat3(&i_oPos.GetXMData()),
			DirectX::XMLoadFloat3(&i_oLookAt.GetXMData()),
			DirectX::XMLoadFloat3(&i_oUp.GetXMData())
		));
	}

	void Matrix::SetTranslation(const Vector3& i_oTranslation)
	{
		m_oInnerMatrix._14 = i_oTranslation.X();
		m_oInnerMatrix._24 = i_oTranslation.Y();
		m_oInnerMatrix._34 = i_oTranslation.Z();
	}

	const Matrix Matrix::Identity(1.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 1.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 1.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 1.0f);

	const Matrix Matrix::Zero(0.0f, 0.0f, 0.0f, 0.0f,
							  0.0f, 0.0f, 0.0f, 0.0f,
							  0.0f, 0.0f, 0.0f, 0.0f,
							  0.0f, 0.0f, 0.0f, 0.0f);
}