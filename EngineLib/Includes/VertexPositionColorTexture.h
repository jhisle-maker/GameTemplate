#pragma once

#include "VertexDeclaration.h"
#include "Color.h"
#include "Vector3.h"
#include "Vector2.h"

namespace GT
{
	struct VertexPositionColorTexture
	{
		const static GT::VertexDeclarationItem VertexDeclarationItems[3];
		const static GT::VertexDeclaration VertexDeclaration;

		Vector3 pos;
		Color color;
		Vector2 uv;
	};
}