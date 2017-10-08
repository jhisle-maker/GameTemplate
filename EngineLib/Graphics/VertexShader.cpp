#pragma once
#include "VertexShader.h"
#include "VertexDeclaration.h"
#include "IGraphicContext.h"
#include "IConstBuffer.h"
#include "ITexture.h"


namespace GT
{
	VertexShader::VertexShader(const std::vector<uint8_t>& i_oShaderFileData, const VertexDeclaration& i_oVertexDeclaration, const IGraphicContext& i_oGraphicContext)
		: m_oGraphicContext(i_oGraphicContext)
		, m_poApiVertexShaderWrapper(i_oGraphicContext.CreateApiVertexShader(i_oShaderFileData, i_oVertexDeclaration))
	{
		//Nothing to do here
	}

	VertexShader::~VertexShader()
	{
		//Nothing to do here
	}

	void VertexShader::BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const
	{
		m_oGraphicContext.BindVertexShaderConstBuffer(i_oConstBuffer.GetApiWrapper());
	}

	void VertexShader::BindTexture(const ITexture& i_oTexture) const
	{
		m_oGraphicContext.BindVertexShaderTexture(i_oTexture.GetApiWrapper());
	}
}