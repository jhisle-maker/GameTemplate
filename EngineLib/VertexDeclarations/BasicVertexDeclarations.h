#pragma once

#include "Graphics\VertexDeclaration.h"
#include "Math\Vector3.h"
#include "Math\Vector2.h"

namespace GT
{
	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		const static GT::VertexDeclarationItem VertexDeclarationItems[2];
		const static GT::VertexDeclaration VertexDeclaration;

		GT::Vector3 pos;
		GT::Vector3 color;
	};

	struct VertexPositionColorTexture
	{
		const static GT::VertexDeclarationItem VertexDeclarationItems[3];
		const static GT::VertexDeclaration VertexDeclaration;

		GT::Vector3 pos;
		GT::Vector3 color;
		GT::Vector2 uv;
	};
}