#ifndef SYNERGON_RHI_TESTS_TESTCLASSES_HPP
#define SYNERGON_RHI_TESTS_TESTCLASSES_HPP

#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>
#include <string>

namespace Synergon::Rhi {
	inline ApiChoice StringToApiChoice(const std::string& apiChoice) {
		if (apiChoice == "Directx12") {
			return ApiChoice::eDirectx12;
		}
		if (apiChoice == "Vulkan") {
			return ApiChoice::eVulkan;
		}

		return ApiChoice::eCustom;
	}

	class DeviceTest : public ::testing::TestWithParam<std::string> {};

	class BufferTest : public ::testing::TestWithParam<std::string> {};

	class CommandAllocatorTest : public ::testing::TestWithParam<std::string> {};

	class CommandBufferTest : public ::testing::TestWithParam<std::string> {};

	class CommandQueueTest : public ::testing::TestWithParam<std::string> {};

	class DisplayTest : public ::testing::TestWithParam<std::string> {};

	class FenceTest : public ::testing::TestWithParam<std::string> {};

	class PipelineLayoutTest : public ::testing::TestWithParam<std::string> {};

	class PipelineTest : public ::testing::TestWithParam<std::string> {};

	class SamplerTest : public ::testing::TestWithParam<std::string> {};

	class ShaderInputContainerTest : public ::testing::TestWithParam<std::string> {};

	class ShaderInputLayoutTest : public ::testing::TestWithParam<std::string> {};

	class TextureTest : public ::testing::TestWithParam<std::string> {};

	class TextureViewTest : public ::testing::TestWithParam<std::string> {};

	class ShaderTest : public ::testing::TestWithParam<std::string> {};

	class RenderTest : public ::testing::TestWithParam<std::string> {};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_TESTS_TESTCLASSES_HPP
