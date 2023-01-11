SamplerState g_SamplerLinear : register(s0); // サンプラー


struct PerInstanceData
{
    matrix instanceMat;
    float4 color;


};

StructuredBuffer<PerInstanceData> g_pInstanceData : register(t8);
Texture2D g_Tex : register(t9); // テクスチャ


struct VS_IN
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
    uint instanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    uint id : ID;
};

cbuffer ConstantBufferWorld : register(b0)
{
    matrix World;
}

cbuffer ConstantBufferView : register(b1)
{
    matrix View;
}

cbuffer ConstantBufferProjection : register(b2)
{
    matrix Projection;
}

VS_OUT VS(VS_IN input)
{
    VS_OUT output;
    output.pos = mul(input.pos, g_pInstanceData[input.instanceID].instanceMat);
    output.id = input.instanceID;
    
    //output.pos = mul(output.pos, View);
    //output.pos = mul(output.pos, Projection);
    output.uv = input.uv;
    output.color = input.color;
    
    return output;
};

float4 PS(VS_OUT input) : SV_Target
{
    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.uv);
    texcol.rgba = 1.0f;
    return texcol;
};