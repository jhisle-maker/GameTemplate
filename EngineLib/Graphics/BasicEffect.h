#pragma once

//START FORWARD DECL
namespace GT { class IGraphicDevice; }
namespace GT { class IGraphicContext; }
//END FORWARD DECL

namespace GT
{
	class BasicEffect
	{
	public:
		BasicEffect(const IGraphicDevice& i_oGraphicDevice, const IGraphicContext& i_oGraphicContext);
		~BasicEffect();

	private:
		const IGraphicDevice& m_oGraphicDevice;
		const IGraphicContext& m_oGraphicContext;
	};
}

