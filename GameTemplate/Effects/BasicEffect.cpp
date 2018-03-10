#include "pch.h"

#include "BasicEffect.h"
#include "Common.h"
#include "Matrix.h"
#include "IGraphicManager.h"
#include "IContentManager.h"
#include "IGraphicDevice.h"
#include "IGraphicContext.h"
#include "IVertexShader.h"
#include "IPixelShader.h"
#include "ITexture.h"
#include "ISamplerState.h"
#include "Color.h"
#include "VertexPositionColor.h"
#include "VertexPositionColorTexture.h"

namespace GT
{
	const ObjectId BasicEffect::s_oPositionColorPSId = ObjectId("PositionColorPixelShader.cso");
	const ObjectId BasicEffect::s_oPositionColorVSId = ObjectId("PositionColorVertexShader.cso");
	const ObjectId BasicEffect::s_oPositionColorTexturePSId = ObjectId("PositionColorTexturePixelShader.cso");
	const ObjectId BasicEffect::s_oPositionColorTextureVSId = ObjectId("PositionColorTextureVertexShader.cso");

	BasicEffect::BasicEffect
	(
		const IGraphicManager& i_oGraphicManager,
		IContentManager& i_oContentManager
	)
		: m_oGraphicDevice(i_oGraphicManager.GetGraphicDevice())
		, m_bUpdateConstBuffer(false)
		, m_poViewPtr(nullptr)
		, m_poModelPtr(nullptr)
		, m_poProjectionPtr(nullptr)
		, m_poTexture(nullptr)
		, m_oConstBuffer(m_oConstBufferData, i_oGraphicManager.GetGraphicContext())
		, m_eSelectedShader(SelectedShader::ePOSITIONCOLOR)
		, m_oPositionColorPS(i_oContentManager.LoadPixelShader(s_oPositionColorPSId))
		, m_oPositionColorVS(i_oContentManager.LoadVertexShader(s_oPositionColorVSId, VertexPositionColor::VertexDeclaration))
		, m_oPositionColorTexturePS(i_oContentManager.LoadPixelShader(s_oPositionColorTexturePSId))
		, m_oPositionColorTextureVS(i_oContentManager.LoadVertexShader(s_oPositionColorTextureVSId, VertexPositionColorTexture::VertexDeclaration))
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

