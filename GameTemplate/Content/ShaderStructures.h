#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"
#include "VertexDeclaration.h"

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