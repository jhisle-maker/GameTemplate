#include "BasicVertexDeclarations.h"

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

	const GT::VertexDeclarationItem VertexPositionColorTexture::VertexDeclarationItems[3] =
	{
		{ GT::VertexUsage::POSITION, GT::VertexType::RGB_FLOAT32 },
		{ GT::VertexUsage::COLOR, GT::VertexType::RGBA_UINT8 },
		{ GT::VertexUsage::TEXTURE, GT::VertexType::RG_FLOAT32 }
	};

	const GT::VertexDeclaration VertexPositionColorTexture::VertexDeclaration =
	{
		VertexPositionColorTexture::VertexDeclarationItems,
		3u
	};
}