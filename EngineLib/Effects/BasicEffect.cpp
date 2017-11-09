#include "BasicEffect.h"
#include "Graphics\IGraphicDevice.h"
#include "Graphics\IGraphicContext.h"
#include "Graphics\IVertexShader.h"
#include "Graphics\IPixelShader.h"
#include "Graphics\ITexture.h"
#include "Graphics\Color.h"
#include "Services\IShaderManagerService.h"
#include "Math\Matrix.h"

namespace GT
{
	BasicEffect::BasicEffect(const IGraphicDevice& i_oGraphicDevice, const IGraphicContext& i_oGraphicContext, const IShaderManagerService& i_oShaderManagerService)
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
				const IVertexShader& oPositionColorVS = m_oShaderManagerService.GetPositionColorVS();
				const IPixelShader& oPositionColorPS = m_oShaderManagerService.GetPositionColorPS();

				oPositionColorVS.BindConstantBuffer(m_oConstBuffer);

				m_oGraphicDevice.BindVertexShader(oPositionColorVS);
				m_oGraphicDevice.BindPixelShader(oPositionColorPS);
		}
		break;

		case GT::BasicEffect::ePOSITIONTEXTURE:
		{
			const IVertexShader& oPositionColorTextureVS = m_oShaderManagerService.GetPositionColorTextureVS();
			const IPixelShader& oPositionColorTexturePS = m_oShaderManagerService.GetPositionColorTexturePS();

			oPositionColorTextureVS.BindConstantBuffer(m_oConstBuffer);
			oPositionColorTexturePS.BindTexture(*m_poTexture);
			//m_poPositionColorTexturePixelShader.BindSamplerState(*m_poSamplerState);

			m_oGraphicDevice.BindVertexShader(oPositionColorTextureVS);
			m_oGraphicDevice.BindPixelShader(oPositionColorTexturePS);
		}
		break;

		default:
			break;
		}	
	}
}

