#pragma once

#include "Math\Vector3.h"
#include "Math\Matrix.h"
#include "Graphics\VertexDeclaration.h"

namespace GameTemplate
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		GT::Matrix model;
		GT::Matrix view;
		GT::Matrix projection;
		/*DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;*/
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		const static GT::VertexDeclarationItem VertexDeclarationItems[2];
		const static GT::VertexDeclaration VertexDeclaration;

		GT::Vector3 pos;
		GT::Vector3 color;
	};
}