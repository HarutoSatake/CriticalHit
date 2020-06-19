#include "Particle.hlsli"


Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 d = tex2.Sample(samLinear, input.Tex);
	float4 b = float4(0.0f, 0.0f, 0.0f, 1.0f);
	if (d.r < Time.x)
	{
		b.a = 0.0f;
	}
	return b;
}