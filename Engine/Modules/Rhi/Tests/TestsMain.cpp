#include "TestClasses.hpp"

namespace Synergon::Rhi {
	INSTANTIATE_TEST_SUITE_P(
	    TestsDevice, DeviceTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsBuffer, BufferTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsBufferView, BufferViewTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsCommandAllocator, CommandAllocatorTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsCommandBuffer, CommandBufferTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsCommandQueue, CommandQueueTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsDisplay, DisplayTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsFence, FenceTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsPipelineLayout, PipelineLayoutTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsPipeline, PipelineTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsSampler, SamplerTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsShaderInputContainer, ShaderInputContainerTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsShaderInputLayout, ShaderInputLayoutTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsTexture, TextureTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsTextureView, TextureViewTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsShader, ShaderTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsShaderInputPool, ShaderInputPoolTest,
	    ::testing::Values("Vulkan", "Directx12"));
	INSTANTIATE_TEST_SUITE_P(
	    TestsRender, RenderTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
