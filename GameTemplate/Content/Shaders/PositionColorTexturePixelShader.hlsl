// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};

SamplerState g_samplerState;
Texture2D g_texture;

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 texColor = g_texture.Sample(g_samplerState, input.uv);
	return input.color + texColor;
}
