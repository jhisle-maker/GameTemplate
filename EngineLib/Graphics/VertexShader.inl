#pragma once

#include "IGraphicContext.h"
#include "VertexShader.h"
#include "IConstBuffer.h"
#include "ITexture.h"

namespace GT
{
	template<typename VertexType>
	VertexShader<VertexType>::VertexShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext& i_oGraphicContext)
		: m_oGraphicContext(i_oGraphicContext)
		, m_poApiVertexShaderWrapper(i_oGraphicContext.CreateApiVertexShader(i_oShaderFileData, VertexType::VertexDeclaration))
	{
		//Nothing to do here
	}

	template<typename VertexType>
	VertexShader<VertexType>::~VertexShader()
	{
		//Nothing to do here
	}

	template<typename VertexType>
	void VertexShader<VertexType>::BindConstantBuffer(const IConstBuffer& i_oConstBuffer) const
	{
		m_oGraphicContext.BindVertexShaderConstBuffer(i_oConstBuffer.GetApiWrapper());
	}

	template<typename VertexType>
	void VertexShader<VertexType>::BindTexture(const ITexture& i_oTexture) const
	{
		m_oGraphicContext.BindVertexShaderTexture(i_oTexture.GetApiWrapper());
	}
}