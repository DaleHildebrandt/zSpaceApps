///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       Direct3D11.hlsl
//  Content:    Shaders for the Direct3D 11.0 zSpace code samples
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constant Buffer Variables
///////////////////////////////////////////////////////////////////////////////
Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer cbNeverChanges : register(b0)
{
  float4 meshColor;
};

cbuffer cbChangesEveryFrame : register(b1)
{
  matrix World;
  matrix View;
  matrix Projection;
};

struct VS_INPUT
{
  float4 Pos : POSITION;
  float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////////
// Vertex Shader
///////////////////////////////////////////////////////////////////////////////
PS_INPUT VS(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  output.Pos = mul(input.Pos, World);
  output.Pos = mul(output.Pos, View);
  output.Pos = mul(output.Pos, Projection);
  output.Tex = input.Tex;

  return output;
}


///////////////////////////////////////////////////////////////////////////////
// Pixel Shader
///////////////////////////////////////////////////////////////////////////////
float4 PS(PS_INPUT input) : SV_Target
{
  return txDiffuse.Sample(samLinear, input.Tex) * meshColor;
}