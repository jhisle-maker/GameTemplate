#include "pch.h"
#include "ShaderStructures.h"

namespace GameTemplate
{
	const GT::VertexDeclarationItem VertexPositionColor::VertexDeclarationItems[2] =
	{
		{ GT::VertexUsage::POSITION, GT::VertexType::FLOAT32 },
		{ GT::VertexUsage::COLOR, GT::VertexType::FLOAT32 }
	};

	const GT::VertexDeclaration VertexPositionColor::VertexDeclaration = 
	{ 
		VertexPositionColor::VertexDeclarationItems,
		2u
	};
}