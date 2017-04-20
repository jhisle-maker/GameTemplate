#pragma once

#include "IGraphicContext.h"
#include "VertexShader.h"

namespace GT
{
	template<typename VertexType>
	VertexShader<VertexType>::VertexShader(const std::vector<uint8_t>& i_oShaderFileData, const IGraphicContext& i_oGraphicContext)
		: m_poApiVertexShaderWrapper(i_oGraphicContext.CreateApiVertexShader(i_oShaderFileData, VertexType::VertexDeclaration))
	{
		//Nothing to do here
	}

	template<typename VertexType>
	VertexShader<VertexType>::~VertexShader()
	{
		//Nothing to do here
	}
}