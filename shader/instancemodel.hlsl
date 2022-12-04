//#include"psvscommon.hlsl"

//struct PerInstanceData
//{
//    matrix instanceMat;
//};


//StructuredBuffer<PerInstanceData> g_pInstanceData : register(t8);



//struct VS_IN
//{
//    float4 pos : POSITION;
//    float4 normal : NORMAL;
//    float2 uv : TEXCOORD;
//    float4 WPos : TEXCOORD1;
//    uint instanceID : SV_InstanceID;
//};

//struct VS_OUT
//{
//    float4 pos : SV_POSITION;
//    float4 normal : NORMAL;
//    float2 uv:TEXCOORD0;
//    float4 WPos : TEXCOORD1;
//    uint id : ID;
//};


//VS_OUT VS(VS_IN input)
//{
//    VS_OUT output;
//    output.pos = mul(input.pos, g_pInstanceData[input.instanceID].instanceMat);
//    output.WPos = output.pos;
//    output.pos = mul(output.pos, View);
//    output.pos = mul(output.pos, Projection);
//    output.uv = input.uv;

//    float4 N = input.normal;
//    N.w = 0.0f; // 法線はベクトルなのでＷの値を０にする。

//    N = mul(N, World);
//    N = normalize(N);
//    output.normal = N;
	 
//    return output;
//};

//float4 PS(VS_OUT input) : SV_Target
//{
    
//    float4 N = input.normal;
//    float4 L = LightDirection;
//    N.w = 0.0f; // 法線はベクトルなのでＷの値を０にする。
//    L.w = 0.0f; // 光の方向はベクトルなのでＷの値を０にする。

//    N = normalize(N);
//    L = normalize(L);

//    float d = max(0.0, dot(L, N)); //鋭角か鈍角かを調べる　90度＞
//    float4 diffuse = diffuseMaterial * d;

//    float4 H;
//    float4 V = normalize(EyePos - input.WPos);
//    H = normalize(L + V);

//    float s = max(0, dot(N, H));
//    s = pow(s, 50);
//    float4 specular = s * specularMaterial;

//    float4 texcol = g_Tex1.Sample(g_SamplerLinear, input.uv);
//    float4 col = Ambient + specular + diffuse * texcol;
//    col.a = texcol.a;
//    return col;

//};