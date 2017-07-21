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
		FLOAT32 = 0u,
		UINT8 = 1u
	};

	struct VertexDeclarationItem
	{
		VertexUsage Usage;
		VertexType Type;
	};

	struct VertexDeclaration
	{
		const VertexDeclarationItem* VertexDeclarationItems;
		const size_t VertexDeclarationItemsCount;
	};
}