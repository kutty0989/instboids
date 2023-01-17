Texture2D g_Tex1 : register(t0);				    // テクスチャ
Texture2D g_Tex2 : register(t1);				    // テクスチャ
Texture2D g_Tex3 : register(t2);				    // テクスチャ
Texture2D g_Tex4 : register(t3);				    // テクスチャ
Texture2D g_Tex5 : register(t4);				    // テクスチャ
Texture2D g_Tex6 : register(t5);				    // テクスチャ
SamplerState g_SamplerLinear : register(s0);	// サンプラー

//--------------------------------------------------------------------------------------
// コンスタントバッファ
//--------------------------------------------------------------------------------------
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

cbuffer ConstantBufferMaterial : register(b3)
{
	float4	ambientMaterial;
	float4	diffuseMaterial;
	float4	specularMaterial;
}

cbuffer ConstantBufferLight : register(b4)
{
	float4 LightDirection;			// 光の方向
	float4 EyePos;					// 視点位置
	float4 Ambient;
}

cbuffer ConstantBufferViewPort : register(b5)
{
    matrix BoneMatrix[400];
};

cbuffer ConstantBufferColor : register(b6)
{
    float4 albedoColor;//拡散反射光を表すカラー
}

cbuffer TessellationBuffer : register(b7)
{
    float tessellationAmount;
    float gcol;
    float padding[2];
};

cbuffer HightBuffer : register(b8)
{

    float hight;
    float a[3];
 
};


cbuffer ConstantBufferBoneMatrix : register(b9)
{
    uint4 ViewportWidth; // ビューポート幅
    uint4 ViewportHeight; // ビューポート高さ

}

cbuffer BlendBuffer : register(b10)
{

    float blendone;
    float blendtwo;
    float blendthere;
    float blendfour;
 
};

cbuffer HpBuffer : register(b11)
{

    float hp;
    float buff[3];
 
};

////アルベドマップ
//Texture2D<float4> g_albedo : register(t0);

////法線マップ
//Texture2D<float4> g_normalMap : register(t1);

////メタリックスムースマップ　ｒにメタリック、aに滑らかさ
//Texture2D<float4> g_metallicSmoothMap : register(t2);
//--------------------------------------------------------------------------------------
// 構造体定義
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
	float2 Tex : TEXCOORD0;
	float4 WPos : TEXCOORD1;
	float4 Normal : TEXCOORD2;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 texel : TEXCOORD;
};


struct HS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
}; //20


struct HS_CONSTANT_OUTPUT
{
    float factor[3] : SV_TessFactor;
    float inner_factor : SV_InsideTessFactor;
};
struct DS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
   
};

struct InstancingMatrix
{
    float4 Position;
    float4 TexturePosition;
    float4 Color;
    float4 Dummy;
   
};

cbuffer SpriteInstancingBuffer : register(b12)
{
    InstancingMatrix SpriteInstancingMatrix[1024];
}