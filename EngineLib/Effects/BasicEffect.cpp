#include "BasicEffect.h"
#include "Utils\Common.h"
#include "Math\Matrix.h"
#include "Graphics\IGraphicDevice.h"
#include "Graphics\IGraphicContext.h"
#include "Graphics\IVertexShader.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\ITexture.h"
#include "Graphics\ISamplerState.h"
#include "Graphics\Color.h"
#include "Services\IShaderManagerService.h"

namespace GT
{
	const ObjectId BasicEffect::s_oPositionColorPSId = ObjectId("PositionColorPS");
	const ObjectId BasicEffect::s_oPositionColorVSId = ObjectId("PositionColorVS");
	const ObjectId BasicEffect::s_oPositionColorTexturePSId = ObjectId("PositionColorTexturePS");
	const ObjectId BasicEffect::s_oPositionColorTextureVSId = ObjectId("PositionColorTextureVS");

	BasicEffect::BasicEffect
	(
		const IGraphicDevice& i_oGraphicDevice, 
		const IGraphicContext& i_oGraphicContext, 
		IShaderManagerService& i_oShaderManagerService
	)
		: m_oGraphicDevice(i_oGraphicDevice)
		, m_oGraphicContext(i_oGraphicContext)
		, m_oShaderManagerService(i_oShaderManagerService)
		, m_bUpdateConstBuffer(false)
		, m_poViewPtr(nullptr)
		, m_poModelPtr(nullptr)
		, m_poProjectionPtr(nullptr)
		, m_poTexture(nullptr)
		, m_oConstBuffer(m_oConstBufferData, i_oGraphicContext)
		, m_eSelectedShader(SelectedShader::ePOSITIONCOLOR)
		, m_oPositionColorPS(i_oShaderManagerService.GetPixelShader(s_oPositionColorPSId))
		, m_oPositionColorVS(i_oShaderManagerService.GetVertexShader(s_oPositionColorVSId))
		, m_oPositionColorTexturePS(i_oShaderManagerService.GetPixelShader(s_oPositionColorTexturePSId))
		, m_oPositionColorTextureVS(i_oShaderManagerService.GetVertexShader(s_oPositionColorTextureVSId))
	{
		//Nothing to do here
	}

	BasicEffect::~BasicEffect()
	{
		//Nothing to do here
	}

	void BasicEffect::SetView(const Matrix& i_oView) 
	{ 
		m_bUpdateConstBuffer = true;
		m_oConstBufferData.m_oView = i_oView;
	}

	void BasicEffect::SetProjection(const Matrix& i_oProjection) 
	{ 
		m_bUpdateConstBuffer = true;
		m_oConstBufferData.m_oProjection = i_oProjection;
	}

	void BasicEffect::SetModel(const Matrix& i_oModel) 
	{ 
		m_bUpdateConstBuffer = true;
		m_oConstBufferData.m_oModel = i_oModel;
	}

	void BasicEffect::SetTexture(const ITexture& i_oTexture)
	{
		m_poTexture = &i_oTexture;
	}

	void BasicEffect::SetTextureEnabled(const bool i_bEnabled)
	{
		m_eSelectedShader = static_cast<SelectedShader>(i_bEnabled);
	}

	void BasicEffect::SetTextureSampler(const ISamplerState& i_oSamplerState)
	{
		m_poSamplerState = &i_oSamplerState;
	}

	void BasicEffect::Apply()
	{
		if (m_bUpdateConstBuffer == true)
		{
			m_bUpdateConstBuffer = false;
			m_oConstBuffer.Update(m_oConstBufferData);			
		}

		switch (m_eSelectedShader)
		{
		case GT::BasicEffect::ePOSITIONCOLOR:
		{
				m_oPositionColorVS.BindConstantBuffer(m_oConstBuffer);

				m_oGraphicDevice.BindVertexShader(m_oPositionColorVS);
				m_oGraphicDevice.BindPixelShader(m_oPositionColorPS);
		}
		break;

		case GT::BasicEffect::ePOSITIONTEXTURE:
		{
			m_oPositionColorTextureVS.BindConstantBuffer(m_oConstBuffer);
			m_oPositionColorTexturePS.BindTexture(*m_poTexture);

			m_oPositionColorTexturePS.BindSamplerState(*m_poSamplerState);

			m_oGraphicDevice.BindVertexShader(m_oPositionColorTextureVS);
			m_oGraphicDevice.BindPixelShader(m_oPositionColorTexturePS);
		}
		break;

		default:
			break;
		}	
	}
}

