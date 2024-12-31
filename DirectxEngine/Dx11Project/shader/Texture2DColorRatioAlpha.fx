
Texture2D Texture : register(t0);

SamplerState samLinear : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	float ColorRatio;
	float Alpha;
	float2 useless;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = input.Pos;
	output.Tex = input.Tex;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 clr = Texture.Sample(samLinear, input.Tex);
	clr.xyz = saturate(clr.xyz * ColorRatio);
	if(Alpha > 0) clr.a = clr.a * Alpha;
	return clr;
}