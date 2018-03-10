#pragma once

#include<DirectXMath.h>

//START FORWARD DECLS
namespace GT
{ 
	class Vector3; 
}
//END FORWARD DECLS

namespace GT
{
	class Matrix
	{
	public: //STATIC METHODS
		static Matrix Transpose(const Matrix& i_oSourceMatrix);
		static Matrix Perspective(const float i_fFovY, const float i_fAspectRatio, const float i_fNearPlane, const float i_fFarPlane);
		static Matrix Ortographic(const float i_fWidth, const float i_fHeight, const float i_fNearPlane, const float i_fFarPlane);
		static Matrix View(const Vector3& i_oPos, const Vector3& i_oLookAt, const Vector3& i_oUp);
		static Matrix RotationX(const float i_fRadians);
		static Matrix RotationY(const float i_fRadians);
		static Matrix RotationZ(const float i_fRadians);

	public: //CTORS
		Matrix();

		Matrix(float i_f00, float i_f01, float i_f02, float i_f03,
			   float i_f10, float i_f11, float i_f12, float i_f13,
			   float i_f20, float i_f21, float i_f22, float i_f23,
			   float i_f30, float i_f31, float i_f32, float i_f33);

	public: //METHODS
		const Matrix& operator= (const Matrix& i_oOther) 
		{ 
			DirectX::XMStoreFloat4x4(&m_oInnerMatrix, DirectX::XMLoadFloat4x4(&i_oOther.GetXMData())); 
			return *this;
		}
		Matrix(const Matrix& i_oOther) { DirectX::XMStoreFloat4x4(&m_oInnerMatrix, DirectX::XMLoadFloat4x4(&i_oOther.GetXMData()));	}
		Matrix(const DirectX::XMMATRIX& i_oOther) { DirectX::XMStoreFloat4x4(&m_oInnerMatrix, i_oOther); }
		inline const DirectX::XMFLOAT4X4& GetXMData() const { return m_oInnerMatrix; }
		const DirectX::XMMATRIX ToXMMatrix() const { return DirectX::XMLoadFloat4x4(&m_oInnerMatrix); }

	public:
		void SetTranslation(const Vector3& i_oTranslation);

	private:
		DirectX::XMFLOAT4X4 m_oInnerMatrix;

	public:
		static const Matrix Identity;
		static const Matrix Zero;
	};
};
