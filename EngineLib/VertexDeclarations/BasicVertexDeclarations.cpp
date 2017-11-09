#include "BasicVertexDeclarations.h"

namespace GT
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

	const GT::VertexDeclarationItem VertexPositionColorTexture::VertexDeclarationItems[3] =
	{
		{ GT::VertexUsage::POSITION, GT::VertexType::FLOAT32 },
		{ GT::VertexUsage::COLOR, GT::VertexType::FLOAT32 },
		{ GT::VertexUsage::TEXTURE, GT::VertexType::FLOAT32 }
	};

	const GT::VertexDeclaration VertexPositionColorTexture::VertexDeclaration =
	{
		VertexPositionColorTexture::VertexDeclarationItems,
		3u
	};
}