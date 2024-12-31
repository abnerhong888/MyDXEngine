//--------------------------------------------------------------------------------------
// File: Dx11Texture.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

struct s_Light
{
	float3 dir;
	float useless;
	float4 ambient;
	float4 diffuse;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 Rotation;
	s_Light light;
	float alpha;
	float3 COM;
}


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Pos : POSITION;
	float4 Normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	input.Pos.x -= COM.x;
	input.Pos.y -= COM.y;
	input.Pos.z -= COM.z;

	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, Rotation);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Normal = mul(input.Normal, Rotation);

  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	
	input.Normal.xyz = normalize(input.Normal.xyz);

	float3 finalColor;

	float4 color = float4(0.0, 0.5 ,0.0, alpha);

	finalColor = (color* light.ambient).xyz;
	finalColor += saturate(dot(light.dir, input.Normal.xyz) * light.diffuse.xyz * color.xyz);

	return float4(finalColor, alpha);

}
