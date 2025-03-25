struct Vertex
{
    [[vk::location(0)]]
    float3 Position : POSITION;

    [[vk::location(1)]]
    float3 Color    : COLOR;
};

struct VertexOutput
{
    float4 Position : SV_Position; // HLSL system semantic
    [[vk::location(0)]]
    float3 Color    : COLOR;
};

struct FragmentInput
{
    [[vk::location(0)]]
    float3 Color : COLOR;
};

[[vk::binding(0, 0)]]
Texture2D<float4> tex0;
[[vk::binding(1, 0)]]
Texture2D<float4> tex1;

[shader("vertex")]
VertexOutput vsmain(Vertex v)
{
    VertexOutput output;
    output.Position = float4(v.Position, 1.0);
    output.Color    = v.Color;
    return output;
}

[shader("fragment")]
float4 fsmain(FragmentInput input) : SV_Target
{
    return float4(input.Color, 1.0);
}
