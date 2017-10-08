#pragma once

#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Math\Matrix.h"
#include "Graphics\VertexDeclaration.h"

namespace GT
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionData
	{
		GT::Matrix model;
		GT::Matrix view;
		GT::Matrix projection;
	};

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