#include	"psvscommon.hlsl"


//
//
VS_OUTPUT main(float3 Pos : POSITION, float4 Col : COLOR, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output;
   
    //VS_OUTPUT Out;
    output.Pos = float4(Pos,1.0f);
    output.Color = Col;
    
    output.Tex = Tex;
    float3 pos = Pos;
    pos.x += 100.0f;
    pos.y += 5.0f;
    pos.z += 50.0f;
    return output;
    
}
