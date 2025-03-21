#pragma once

#include "Synergon/Rhi/IBufferView.hpp"
#include "Synergon/Rhi/ISampler.hpp"
#include "Synergon/Rhi/IShaderInputLayout.hpp"
#include "Synergon/Rhi/IShaderInputPool.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>

/*
	buffer1
	buffer2
	buffer3
	texture1
	texture2

    DescriptorHeap [0 1 2 3 4 5]

    buffer1View = DescriptorHeap[0]
	buffer2View = DescriptorHeap[1]
	buffer3View = DescriptorHeap[2]
	texture1View = DescriptorHeap[3]
	texture2View = DescriptorHeap[4]

	VkDescriptorPool;

	VkDescriptorSet1;
	VkDescriptorSet2;

	textureView != pool;


*/

namespace Synergon::Rhi {
	class IShaderInputContainer {
	   public:
		virtual ~IShaderInputContainer() = default;

		virtual void bindSampledTexture(uint32_t binding, const std::shared_ptr<ITextureView>& textureView) = 0;
		virtual void bindStorageTexture(uint32_t binding, const std::shared_ptr<ITextureView>& textureView) = 0;
		virtual void bindUniformBuffer(uint32_t binding, const std::shared_ptr<IBufferView>& bufferView)    = 0;
		virtual void bindStorageBuffer(uint32_t binding, const std::shared_ptr<IBufferView>& bufferView)    = 0;

		virtual void bindSampler(uint32_t binding, const std::shared_ptr<ISampler>& sampler) = 0;

		virtual std::shared_ptr<IShaderInputLayout> getLayout() const = 0;
		virtual std::shared_ptr<IShaderInputPool>   getPool() const   = 0;
	};
}  // namespace Synergon::Rhi
