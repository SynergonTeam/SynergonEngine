#pragma once

#include <d3d12.h>
#include <stdexcept>
#include "Synergon/Rhi/IDevice.hpp"

namespace Synergon::Rhi {
	//------------------------------------------------------------------------------------------------
	struct CD3DX12_HEAP_PROPERTIES : public D3D12_HEAP_PROPERTIES
	{
		CD3DX12_HEAP_PROPERTIES() = default;
		explicit CD3DX12_HEAP_PROPERTIES(const D3D12_HEAP_PROPERTIES &o) :
			D3D12_HEAP_PROPERTIES(o)
		{}
		CD3DX12_HEAP_PROPERTIES(
			D3D12_CPU_PAGE_PROPERTY cpuPageProperty,
			D3D12_MEMORY_POOL memoryPoolPreference,
			UINT creationNodeMask = 1,
			UINT nodeMask = 1 )
		{
			Type = D3D12_HEAP_TYPE_CUSTOM;
			CPUPageProperty = cpuPageProperty;
			MemoryPoolPreference = memoryPoolPreference;
			CreationNodeMask = creationNodeMask;
			VisibleNodeMask = nodeMask;
		}
		explicit CD3DX12_HEAP_PROPERTIES(
			D3D12_HEAP_TYPE type,
			UINT creationNodeMask = 1,
			UINT nodeMask = 1 )
		{
			Type = type;
			CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			CreationNodeMask = creationNodeMask;
			VisibleNodeMask = nodeMask;
		}
		bool IsCPUAccessible() const
		{
			return Type == D3D12_HEAP_TYPE_UPLOAD || Type == D3D12_HEAP_TYPE_READBACK || (Type == D3D12_HEAP_TYPE_CUSTOM &&
				(CPUPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE || CPUPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_BACK));
		}
	};
	inline bool operator==( const D3D12_HEAP_PROPERTIES& l, const D3D12_HEAP_PROPERTIES& r )
	{
		return l.Type == r.Type && l.CPUPageProperty == r.CPUPageProperty &&
			l.MemoryPoolPreference == r.MemoryPoolPreference &&
			l.CreationNodeMask == r.CreationNodeMask &&
			l.VisibleNodeMask == r.VisibleNodeMask;
	}
	inline bool operator!=( const D3D12_HEAP_PROPERTIES& l, const D3D12_HEAP_PROPERTIES& r )
	{ return !( l == r ); }
	//------------------------------------------------------------------------------------------------

	/**
	 * @brief Utility functions for DirectX 12
	 */
	class SDx12Utils {
	public:
		// This class and function is taken from the DirectX-Graphics-Samples repository on GitHub,
		// found it very useful for error handling, but we need to do something like DXSampleHelper
		// link: https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HelloWorld/src/HelloTriangle
		/************************************************************************************/
		static inline std::string HrToString(HRESULT hr) {
			char s_str[64] = {};
			sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
			return std::string(s_str);
		}

		class HrException : public std::runtime_error {
		   public:
			HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}

			HRESULT Error() const { return m_hr; }

		   private:
			const HRESULT m_hr;
		};

		static inline void ThrowIfFailed(HRESULT hr) {
			if (FAILED(hr)) {
				throw HrException(hr);
			}
		}
		/************************************************************************************/

		/**
		 * @brief Converts engine texture dimension to DirectX 12 resource dimension
		 * @param dim The engine texture dimension
		 * @return D3D12 resource dimension
		 */
		static D3D12_RESOURCE_DIMENSION textureDimensionToDX12(TextureDimension dim);

		/**
		 * @brief Converts engine texture format to DirectX 12 DXGI format
		 * @param format The engine texture format
		 * @return DXGI format
		 */
		static DXGI_FORMAT textureFormatToDXGI(TextureFormat format);
	};

} // namespace Synergon::Rhi