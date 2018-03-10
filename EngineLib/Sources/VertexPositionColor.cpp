#include "VertexPositionColor.h"

namespace GT
{
	const GT::VertexDeclarationItem VertexPositionColor::VertexDeclarationItems[2] =
	{
		{ GT::VertexUsage::POSITION, GT::VertexType::RGB_FLOAT32 },
		{ GT::VertexUsage::COLOR, GT::VertexType::RGBA_UINT8 }
	};

	const GT::VertexDeclaration VertexPositionColor::VertexDeclaration =
	{
		VertexPositionColor::VertexDeclarationItems,
		2u
	};
}