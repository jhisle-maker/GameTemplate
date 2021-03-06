﻿#pragma once

#include "..\Common\GraphicDeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

#include "ConstBuffer.h"
#include "IIndexBuffer.h"
#include "IVertexBuffer.h"
#include "ITexture.h"
#include "ISamplerState.h"

#include "Effects\BasicEffect.h"

#include "IVertexShader.h"
#include "IPixelShader.h"
#include "PerspectiveCamera.h"
#include "OrtographicalCamera.h"
#include "IFileLoaderService.h"

//Forward decls
namespace GT { class IGraphicDevice; }
namespace GT { class IGraphicContext; }

namespace GT
{
	// This sample renderer instantiates a basic rendering pipeline.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(DX::GraphicDeviceResources& deviceResources, const IGraphicDevice& i_oGraphicDevice, const IGraphicContext& i_oGraphicContext);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }


	private:
		void Rotate(float radians);

	private:

		//GT stuff
		const IGraphicDevice& m_oGraphicDevice;
		const IGraphicContext& m_oGraphicContext;

		std::unique_ptr<BasicEffect> m_poBasicEffect;

		std::unique_ptr<IIndexBuffer> m_poIndexBuffer;
		std::unique_ptr<IVertexBuffer> m_poVertexBuffer;
		std::unique_ptr<ConstBuffer<ModelViewProjectionData>> m_poConstBuffer;
		std::unique_ptr<ITexture> m_poTexture;
		std::unique_ptr<IVertexShader> m_poVertexShader;
		std::unique_ptr<IPixelShader> m_poPixelShader;
		std::unique_ptr<PerspectiveCamera> m_poCamera;
		std::unique_ptr<ISamplerState> m_poSamplerState;
		
		// Cached pointer to device resources.
		DX::GraphicDeviceResources& m_deviceResources;

		// System resources for cube geometry.
		ModelViewProjectionData	m_constantBufferData;
		uint32	m_indexCount;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;
	};
}

