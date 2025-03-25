#pragma once

#include "Synergon/Rhi/IBufferView.hpp"
#include "Synergon/Rhi/ISampler.hpp"
#include "Synergon/Rhi/IShaderInputLayout.hpp"
#include "Synergon/Rhi/IShaderInputPool.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>

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
