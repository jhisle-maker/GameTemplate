#pragma once

#include "Utils\Common.h"
#include "Math\Matrix.h"
#include "Graphics\ConstBuffer.h"

//START FORWARD DECL
namespace GT { class IGraphicDevice; }
namespace GT { class IGraphicContext; }
namespace GT { class IVertexShader; }
namespace GT { class IPixelShader; }
namespace GT { class IShaderManagerService; }
namespace GT { class ITexture; }
namespace GT { class ISamplerState; }
//END FORWARD DECL

namespace GT
{
	class BasicEffect
	{
	public:
		BasicEffect(const IGraphicDevice& i_oGraphicDevice, const IGraphicContext& i_oGraphicContext, IShaderManagerService& i_oShaderManagerService);
		~BasicEffect();

		static const ObjectId s_oPositionColorPSId;
		static const ObjectId s_oPositionColorVSId;
		static const ObjectId s_oPositionColorTexturePSId;
		static const ObjectId s_oPositionColorTextureVSId;

	public:
		void SetView(const Matrix& i_oView);
		void SetProjection(const Matrix& i_oProjection);
		void SetModel(const Matrix& i_oModel);

		void SetTexture(const ITexture& i_oTexture);
		void SetTextureEnabled(const bool i_bEnabled);
		void SetTextureSampler(const ISamplerState& i_oSamplerState);

		void Apply();

	private:
		const IGraphicDevice& m_oGraphicDevice;
		const IGraphicContext& m_oGraphicContext;
		IShaderManagerService& m_oShaderManagerService;

	private:
		struct ConstBufferData
		{
			Matrix m_oModel = Matrix::Identity;
			Matrix m_oView = Matrix::Identity;
			Matrix m_oProjection = Matrix::Identity;
		};

		enum SelectedShader
		{
			ePOSITIONCOLOR = 0,
			ePOSITIONTEXTURE = 1
		};

		bool m_bUpdateConstBuffer;
		SelectedShader m_eSelectedShader;

		const IVertexShader& m_oPositionColorVS;
		const IPixelShader& m_oPositionColorPS;
		const IVertexShader& m_oPositionColorTextureVS;
		const IPixelShader& m_oPositionColorTexturePS;

		const Matrix* m_poViewPtr;
		const Matrix* m_poModelPtr;
		const Matrix* m_poProjectionPtr;

		const ITexture* m_poTexture;
		const ISamplerState* m_poSamplerState;

		ConstBufferData m_oConstBufferData;
		ConstBuffer<ConstBufferData> m_oConstBuffer;
	};
}

