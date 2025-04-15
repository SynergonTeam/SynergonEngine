#pragma once

#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
	class SimpleTriangleRenderTest : public ::testing::TestWithParam<std::string> {
	   public:
		void init();

		std::unique_ptr<IDevice>  m_Device;
		std::unique_ptr<IDisplay> m_Display;

		std::unique_ptr<IPipeline> m_Pipeline;

		std::shared_ptr<IShaderInputContainer> m_ResourceInputContainer;
		std::shared_ptr<IShaderInputContainer> m_SamplerInputContainer;

		std::shared_ptr<IBufferView>  m_VertexBufferView;
		std::shared_ptr<ITextureView> m_TriangleTextureView;

		std::shared_ptr<IShaderInputContainer> m_ShaderResourceInputContainer;
		std::shared_ptr<IShaderInputContainer> m_ShaderSamplerInputContainer;
	};
}  // namespace Synergon::Rhi