#pragma once

#if defined(BX_DX11)
#include "Math\Matrix.h"
#include<memory>
#include<wrl\client.h>

// FORWARD DECLS
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11Buffer;

namespace BX
{
	class DX11GraphicDevice;
}

// END FORWARD DECLS

namespace BX
{
	class DX11BasicEffect
	{

	public:
		DX11BasicEffect
		(
			Microsoft::WRL::ComPtr<ID3D11VertexShader> i_poVertexShader,
			Microsoft::WRL::ComPtr<ID3D11PixelShader> i_poPixelShader,
			const DX11GraphicDevice& i_oGraphicDevice
		);

		virtual ~DX11BasicEffect();

		void Apply(const Matrix& i_oModel, const Matrix& i_oView, const Matrix& i_oProjection);
		
	private:
		void InitConstantBuffer();

	private:
		struct ConstantBufferData
		{
			Matrix m_oModel;
			Matrix m_oView;
			Matrix m_oProjection;
		};

	private:
		ConstantBufferData m_oConstBufferData;

		const DX11GraphicDevice& m_oGraphicDevice;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_poVertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_poPixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_poConstBuffer;
	};
}

#endif