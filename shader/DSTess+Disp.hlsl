#include	"psvscommon.hlsl"

[domain("tri")]
DS_OUTPUT main(HS_CONSTANT_OUTPUT In, float3 UV : SV_DomaInLocation, const OutputPatch<HS_OUTPUT, 3> patch)
{
  
    DS_OUTPUT Out;
 
    float2 uv = patch[0].uv * UV.x + patch[1].uv * UV.y + patch[2].uv * UV.z;
 
    Out.uv = uv;
    
    Out.color = patch[0].color;
    
    float4 height = g_Tex1.SampleLevel(g_SamplerLinear, uv, 0);

    float3 pos = patch[0].Pos * UV.x + patch[1].Pos * UV.y + patch[2].Pos * UV.z;
    Out.pos = float4(pos, 1);
    
    height.x;
    Out.pos.z -= height.x * hight;//çÇÇ≥ÇïœçX

    
    Out.pos = mul(Out.pos,World);
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);

    return Out;
}
//
//

