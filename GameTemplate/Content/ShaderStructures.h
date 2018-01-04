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
}