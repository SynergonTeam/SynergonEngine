#pragma once

#include <gtest/gtest.h>
#include <string>

namespace Synergon::Rhi {
	class DeviceTest : public ::testing::TestWithParam<std::string> {};

	class BufferTest : public ::testing::TestWithParam<std::string> {};

	class BufferViewTest : public ::testing::TestWithParam<std::string> {};

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

	class ShaderInputPoolTest : public ::testing::TestWithParam<std::string> {};
}  // namespace Synergon::Rhi
