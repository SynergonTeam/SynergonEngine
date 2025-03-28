#pragma once

#include <cstdint>

namespace Synergon::Rhi {
	enum class MemoryUsage {
		eGpu      = 0,
		eCpu      = 1,
		eCpuToGpu = 2,
		eGpuToCpu = 3,
	};

	struct BufferUsage {
		typedef uint8_t Type;

		enum Flags : uint8_t {
			eVertex      = 1 << 0,
			eIndex       = 1 << 1,
			eUniform     = 1 << 2,
			eStorage     = 1 << 3,
			eTransferSrc = 1 << 4,
			eTransferDst = 1 << 5,
			eIndirect    = 1 << 6,
		};
	};

	struct TextureUsage {
		typedef uint8_t Type;

		enum Flags : uint8_t {
			eSampled                = 1 << 0,
			eColorAttachment        = 1 << 1,
			eDepthStencilAttachment = 1 << 5,
			eStorage                = 1 << 2,
			eTransferSrc            = 1 << 3,
			eTransferDst            = 1 << 4,
		};
	};

	enum class TextureDimension {
		e1D   = 0,
		e2D   = 1,
		e3D   = 2,
		eCube = 3,
	};

	enum class TextureViewDimension {
		e1D        = 0,
		e2D        = 1,
		e3D        = 2,
		eCube      = 3,
		e1DArray   = 4,
		e2DArray   = 5,
		eCubeArray = 6,
	};

	struct TextureAspect {
		typedef uint8_t Type;

		enum Flags : uint8_t {
			eUndefined    = 0,
			eColor        = 1 << 0,
			eDepth        = 1 << 2,
			eStencil      = 1 << 3,
			eDepthStencil = eDepth | eStencil,
		};
	};

	enum class TextureFormat {
		eR8Unorm              = 0,
		eR8Snorm              = 1,
		eR8Uint               = 2,
		eR8Sint               = 3,
		eR16Unorm             = 4,
		eR16Snorm             = 5,
		eR16Uint              = 6,
		eR16Sint              = 7,
		eR16Float             = 8,
		eR32Uint              = 9,
		eR32Sint              = 10,
		eR32Float             = 11,
		eRG8Unorm             = 12,
		eRG8Snorm             = 13,
		eRG8Uint              = 14,
		eRG8Sint              = 15,
		eRG16Unorm            = 16,
		eRG16Snorm            = 17,
		eRG16Uint             = 18,
		eRG16Sint             = 19,
		eRG16Float            = 20,
		eRG32Uint             = 21,
		eRG32Sint             = 22,
		eRG32Float            = 23,
		eRGB8Unorm            = 24,
		eRGB8Snorm            = 25,
		eRGB8Uint             = 26,
		eRGB8Sint             = 27,
		eRGB16Unorm           = 28,
		eRGB16Snorm           = 29,
		eRGB16Uint            = 30,
		eRGB16Sint            = 31,
		eRGB16Float           = 32,
		eRGB32Uint            = 33,
		eRGB32Sint            = 34,
		eRGB32Float           = 35,
		eRGBA8Unorm           = 36,
		eRGBA8Snorm           = 37,
		eRGBA8Uint            = 38,
		eRGBA8Sint            = 39,
		eRGBA16Unorm          = 40,
		eRGBA16Snorm          = 41,
		eRGBA16Uint           = 42,
		eRGBA16Sint           = 43,
		eRGBA16Float          = 44,
		eRGBA32Uint           = 45,
		eRGBA32Sint           = 46,
		eRGBA32Float          = 47,
		eDepth16Unorm         = 48,
		eDepth24Unorm         = 49,
		eDepth32Float         = 50,
		eDepth24Stencil8      = 51,
		eDepth32FloatStencil8 = 52,
	};

	enum class Filter {
		eUndefined = 0,
		eNearest   = 1,
		eLinear    = 2,
	};

	enum class AddressMode {
		eUndefined       = 0,
		eRepeat          = 1,
		eMirroredRepeat  = 3,
		eClampToEdge     = 3,
		eClampToBorder   = 4,
		eMirrorClampEdge = 5,
	};

	enum class CompareOp {
		eUndefined    = 0,
		eNever        = 1,
		eLess         = 2,
		eEqual        = 3,
		eLessOrEqual  = 4,
		eGreater      = 5,
		eNotEqual     = 6,
		eGreaterEqual = 7,
		eAlways       = 8,
	};

	struct ShaderStage {
		typedef uint8_t Type;

		enum Flags : uint8_t {
			eVertex   = 1 << 0,
			eFragment = 1 << 1,
			eCompute  = 1 << 2,
		};
	};

	enum class ShaderResourceInputType {
		eSampledTexture = 0,
		eStorageTexture = 1,
		eUniformBuffer  = 2,
		eStorageBuffer  = 3,
	};

	enum class ShaderInputType {
		eResource               = 0,
		eSampler                = 1,
		eColorAttachment        = 2,
		eDepthStencilAttachment = 3,
	};

	enum class CompositeAlphaMode {
		eUndefined      = 0,
		eOpaque         = 1,
		ePreMultiplied  = 2,
		ePostMultiplied = 3,
		eInherit        = 4,
	};

	enum class PresentMode {
		eFifo        = 0,
		eFifoRelaxed = 1,
		eImmediate   = 2,
		eMailbox     = 3,
	};

	enum class SampleCount {
		e1  = 1,
		e2  = 2,
		e4  = 4,
		e8  = 8,
		e16 = 16,
	};

	enum class VertexStepMode {
		eVertex   = 0,
		eInstance = 1,
	};

	enum class VertexFormat {
		eUint8           = 0,
		eUint8x2         = 1,
		eUint8x4         = 2,
		eSint8           = 3,
		eSint8x2         = 4,
		eSint8x4         = 5,
		eUnorm8          = 6,
		eUnorm8x2        = 7,
		eUnorm8x4        = 8,
		eSnorm8          = 9,
		eSnorm8x2        = 10,
		eSnorm8x4        = 11,
		eUint16          = 12,
		eUint16x2        = 13,
		eUint16x4        = 14,
		eSint16          = 15,
		eSint16x2        = 16,
		eSint16x4        = 17,
		eUnorm16         = 18,
		eUnorm16x2       = 19,
		eUnorm16x4       = 20,
		eSnorm16         = 21,
		eSnorm16x2       = 22,
		eSnorm16x4       = 23,
		eFloat16         = 24,
		eFloat16x2       = 25,
		eFloat16x4       = 26,
		eFloat32         = 27,
		eFloat32x2       = 28,
		eFloat32x3       = 29,
		eFloat32x4       = 30,
		eUint32          = 31,
		eUint32x2        = 32,
		eUint32x3        = 33,
		eUint32x4        = 34,
		eSint32          = 35,
		eSint32x2        = 36,
		eSint32x3        = 37,
		eSint32x4        = 38,
		eUnorm10_10_10_2 = 39,
		eUnorm8x4BGRA    = 40,
	};

	enum class PrimitiveTopology {
		ePointList     = 0,
		eLineList      = 1,
		eLineStrip     = 2,
		eTriangleList  = 3,
		eTriangleStrip = 4,
		eTriangleFan   = 5,
	};

	enum class CullMode {
		eNone  = 0,
		eFront = 1,
		eBack  = 2,
	};

	enum class FrontFace {
		eClockWise        = 0,
		eCounterClockWise = 1,
	};

	enum class PolygoneMode {
		eFill  = 0,
		eLine  = 1,
		ePoint = 2,
	};

	enum class BlendFactor {
		eZero                  = 0,
		eOne                   = 1,
		eSrcColor              = 2,
		eOneMinusSrcColor      = 3,
		eDstColor              = 4,
		eOneMinusDstColor      = 5,
		eSrcAlpha              = 6,
		eOneMinusSrcAlpha      = 7,
		eDstAlpha              = 8,
		eOneMinusDstAlpha      = 9,
		eConstantColor         = 10,
		eOneMinusConstantColor = 11,
		eConstantAlpha         = 12,
		eOneMinusConstantAlpha = 13,
		eSrcAlphaSaturate      = 14,
		eSrc1Color             = 15,
		eOneMinusSrc1Color     = 16,
		eSrc1Alpha             = 17,
		eOneMinusSrc1Alpha     = 18,
	};

	enum class BlendOp {
		eAdd             = 0,
		eSubtract        = 1,
		eReverseSubtract = 2,
		eMin             = 3,
		eMax             = 4,
	};

	enum class StencilOp {
		eKeep           = 0,
		eZero           = 1,
		eReplace        = 2,
		eInvert         = 3,
		eIncrementClamp = 4,
		eDecrementClamp = 5,
		eIncrementWrap  = 6,
		eDecrementWrap  = 7,
	};

	enum class CommandType {
		Graphics = 0,
		Compute  = 1,
		Copy     = 2,
		Bundle   = 3,
	};

	enum class ShaderCodeType {
		eShaderSlang    = 0,
		eNativeByteCode = 1,
	};

	enum class BufferMapType {
		eRead      = 0,
		eWrite     = 1,
		eReadWrite = 2,
	};

	enum class BufferMapState {
		eUnmapped        = 0,
		eMappedRead      = 1,
		eMappedWrite     = 2,
		eMappedReadWrite = 3,
	};

	enum class LoadOp {
		eLoad     = 0,
		eClear    = 1,
		eDontCare = 2,
	};

	enum class StoreOp {
		eStore     = 0,
		eDontCare  = 1,
		eDontClear = 2,
	};

	enum class IndexType {
		eUint16 = 0,
		eUint32 = 1,
	};
}  // namespace Synergon::Rhi
