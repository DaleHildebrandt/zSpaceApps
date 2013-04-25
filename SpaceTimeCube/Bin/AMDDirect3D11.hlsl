///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       LeftRightDetect.hlsl
//  Content:    Creates the pipeline for combining the left and right textures
//              to generate a stereo frame for the L/R detection algorithm
//
///////////////////////////////////////////////////////////////////////////////

struct QuadVS_Input
{
  float4 Pos : POSITION;
  float2 Tex : TEXCOORD0;
};

struct QuadVS_Output
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
};

SamplerState PointSampler
{
  Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
  AddressU = Clamp;
  AddressV = Clamp;
};

Texture2D<float4> tex : register( t0 );

///////////////////////////////////////////////////////////////////////////////
//
// Vertex shader for drawing the full screen quad
//
///////////////////////////////////////////////////////////////////////////////

QuadVS_Output QuadVS( QuadVS_Input Input )
{
  QuadVS_Output Output;
  Output.Pos = Input.Pos;
  Output.Tex = Input.Tex;
  return Output;
}

///////////////////////////////////////////////////////////////////////////////
//
// Pixel shader for copying the texture to the full screen quad
//
///////////////////////////////////////////////////////////////////////////////

float4 CopyPS(QuadVS_Output Input) : SV_Target
{
  return tex.Sample(PointSampler, Input.Tex);
}
