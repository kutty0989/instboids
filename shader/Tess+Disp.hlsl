#include	"psvscommon.hlsl"


struct HS_CONSTANT_OUTPUT
{
    float factor[4] : SV_TessFactor;
    float inner_factor[2] : SV_InsideTessFactor;
};

struct HS_OUTPUT
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};//20

struct DS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

//
//
//
VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD0)
{
    VS_OUTPUT Out;
    Out.Pos = Pos;
    Out.Tex = Tex;

    return Out;
}
//
////40
//
HS_CONSTANT_OUTPUT HSConstant(InputPatch<VS_OUTPUT, 4> ip, uint pid : SV_PrimitiveID)
{
    HS_CONSTANT_OUTPUT Out;
    float divide = 64;

    Out.factor[0] = divide;
    Out.factor[1] = divide;
    Out.factor[2] = divide;
    Out.factor[3] = divide;

    Out.inner_factor[0] = divide; //u 縦の分割数（横のラインを何本ひくか）
    Out.inner_factor[1] = divide; //v

    return Out;
}
//
//
//
[domain("quad")]//60
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("HSConstant")]
HS_OUTPUT HS(InputPatch<VS_OUTPUT, 4> ip, uint cpid : SV_OutputControlPointID, uint pid : SV_PrimitiveID)
{
    HS_OUTPUT Out;
    Out.pos = ip[cpid].Pos;
    Out.uv = ip[cpid].Tex;

    return Out;
}
//
//
//
[domain("quad")]
DS_OUTPUT DS(HS_CONSTANT_OUTPUT In, float2 UV : SV_DomaInLocation, const OutputPatch<HS_OUTPUT, 4> patch)
{
    DS_OUTPUT Out;
    //80
    float2 top_uv = lerp(patch[0].uv, patch[1].uv, UV.x);
    float2 bottom_uv = lerp(patch[3].uv, patch[2].uv, UV.x);
    float2 uv = float2(lerp(top_uv, bottom_uv, UV.y));
    Out.uv = uv;

    float4 height = g_Tex.SampleLevel(g_SamplerLinear, uv, 0) / 4;

    float4 top_pos = lerp(patch[0].pos, patch[1].pos, UV.x);
    float4 bottom_pos = lerp(patch[3].pos, patch[2].pos, UV.x);
    Out.pos = lerp(top_pos, bottom_pos, UV.y);
    Out.pos.y += height.x;
    
    Out.pos = mul(Out.pos, World);
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);


    return Out;
}
//
//
//
float4 PS(DS_OUTPUT In) : SV_Target
{
    float4 col = g_Tex.SampleLevel(g_SamplerLinear, In.uv, 0);
    return col;
}

