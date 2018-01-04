#pragma once

namespace GT
{
	enum VertexUsage
	{
		POSITION = 0u,
		COLOR = 1u,
		NORMAL = 2u,
		TEXTURE = 3u
	};

	enum VertexType
	{
		RGB_FLOAT32 = 0u,
		RGBA_UINT8 = 1u,
		RG_FLOAT32 = 2u,
	};

	struct VertexDeclarationItem
	{
		VertexUsage Usage;
		VertexType Type;
	};

	struct VertexDeclaration
	{
		const VertexDeclarationItem* VertexDeclarationItems;
		const size_t VertexDeclarationItemsCount = 0u;
	};
}