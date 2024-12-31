
Texture2D Texture : register(t0);

SamplerState LinearBorder : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	float posX;
	float posY;
	float fontX;
	float fontY;
	float fontW;
	float fontH;
	float colorR;
	float colorG;
	float colorB;
	float scaleX;
	float scaleY;
	float useless;
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
	input.Pos.xy = input.Pos.xy + float2(1.0, 1.0);
	output.Pos = float4(posX, posY, 0.0, 0.0) + input.Pos * float4(scaleX, scaleY, 0.0, 1.0) ;
	output.Tex = float2(fontX, fontY) + input.Tex * float2(fontW, fontH) ;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 clr = Texture.Sample(LinearBorder, input.Tex);
	clr.a = saturate(clr.x + clr.y + clr.z);
	clr.xyz = clr.xyz * float3(colorR, colorG, colorB);
	
	return clr;
}