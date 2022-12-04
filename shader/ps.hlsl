//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"



//float CalcdiffuseFromFresnel(float3 N,float L,float V)
//{
//	//法線と光線に向かうベクトルがどれだけ似ているかをない席で求める
//    float dotNL = saturate(dot(N, L));
	
//	//法線と視線に向かうベクトルがどれだけ似ているかを内積で求める
//    float dotNV = saturate(dot(N, V));

//	//法線と光源への方向に依存する拡散反射率と、法線と視線ベクトルに依存する拡散反射率を
//	//乗算して最終的な拡散反射率をもとめる
//    return (dotNL * dotNV);
	
//}

//// ベックマン分布を計算する
//float Beckmann(float m, float t)
//{
//    float t2 = t * t;
//    float t4 = t * t * t * t;
//    float m2 = m * m;
//    float D = 1.0f / (4.0f * m2 * t4);
//    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
//    return D;
//}

//// フレネルを計算。Schlick近似を使用
//float SpcFresnel(float f0, float u)
//{
//    // from Schlick
//    return f0 + (1 - f0) * pow(1 - u, 5);
//}

//float CookTorranceSpecular(float3 L, float3 V, float3 N, float metallic)
//{
//    float microfacet = 0.76f;

//    // 金属度を垂直入射の時のフレネル反射率として扱う
//    // 金属度が高いほどフレネル反射は大きくなる
//    float f0 = metallic;

//    // ライトに向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
//    float3 H = normalize(L + V);

//    // 各種ベクトルがどれくらい似ているかを内積を利用して求める
//    float NdotH = saturate(dot(N, H));
//    float VdotH = saturate(dot(V, H));
//    float NdotL = saturate(dot(N, L));
//    float NdotV = saturate(dot(N, V));

//    // D項をベックマン分布を用いて計算する
//    float D = Beckmann(microfacet, NdotH);

//    // F項をSchlick近似を用いて計算する
//    float F = SpcFresnel(f0, VdotH);

//    // G項を求める
//    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

//    // m項を求める
//    float m = 3.141592f * NdotV * NdotH;

//    // ここまで求めた、値を利用して、Cook-Torranceモデルの鏡面反射を求める
//    return max(F * D * G / m, 0.0);
//}
//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
//float4 main(VS_OUTPUT input) : SV_Target
//{
	
//	float4 N = input.Normal;
//	float4 L = LightDirection;
//	N.w = 0.0f;					// 法線はベクトルなのでＷの値を０にする。
//	L.w = 0.0f;					// 光の方向はベクトルなのでＷの値を０にする。
    
//	//各種マップをサンプリング
//	//アルベドカラー（拡散反射光）
//    float4 albedoColor = g_albedo.Sample(g_SamplerLinear, input.Tex);
	
    
//	//スペキュラーはアルベドカラーと同じにする
//    float3 specColor = albedoColor;
	
//	//金属度
//    float metalic = g_metallicSmoothMap.Sample(g_SamplerLinear, input.Tex).r;
	
//	//滑らかさ
//    float smooth = g_metallicSmoothMap.Sample(g_SamplerLinear, input.Tex).a;
	
   
//	//視線に向かってのびるベクトル計算
//    float3 toEye = normalize(EyePos - input.WPos);
	
//    float3 lig = 0;
	

//		//フレネル反射を考慮した拡散反射を計算
//    float diffuseFromFrenel = CalcdiffuseFromFresnel(N.xyz, -L.x, toEye.x);
		
//		//正規化Lambert拡散反射を求める
//    float NdotL = saturate(dot(N ,-L));
//    float3 lambertDiffuse = L * NdotL / 3.14159265f;
    
//		//最終的な拡散反射光を計算
//    float3 diffuse = albedoColor.rgb * diffuseFromFrenel * lambertDiffuse;
	
//	//Cool_Torranceモデルの鏡面反射率を計算する
//    float3 spec = CookTorranceSpecular(-L.xyz, toEye, N.xyz, smooth) * L;
	
//	//金属度が高ければ、鏡面反射はスペキュラカラー、低ければ白
//	//スペキュラーカラーの強さを鏡面反射率として扱う
//    spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metalic);
	
//	//滑らかさを使って拡散反射光と鏡面反射光を合成する
//	//滑らかさが高ければ、鏡面反射は弱くなる
//    lig += diffuse * (1.0f - smooth) + spec;
	
	
	
//    //N = normalize(N);
//    //L = normalize(L);

  
	
//    //float4 H;
//    //float4 V = normalize(EyePos - input.WPos);
//    //H = normalize(L + V);

//    //float s = max(0, dot(N, H));
//    //s = pow(s, 50);
//    //float4 specular = s * specularMaterial;

//    //float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
   
	
	

//    // 環境光による底上げ
//    lig += Ambient.rgba * albedoColor;

//    float4 finalColor = 1.0f;
//    finalColor.xyz = albedoColor;
//    return finalColor;
	
//	//return col;
//}



float4 main(VS_OUTPUT input) : SV_Target
{
    float4 N = input.Normal;
    float4 L = LightDirection;
    N.w = 0.0f; // 法線はベクトルなのでＷの値を０にする。
    L.w = 0.0f; // 光の方向はベクトルなのでＷの値を０にする。

    N = normalize(N);
    L = normalize(L);

    float d = max(0.0, dot(L, N)); //鋭角か鈍角かを調べる　90度＞
    float4 diffuse = diffuseMaterial * d;

    
	
    float4 H;
    float4 V = normalize(EyePos - input.WPos);
    H = normalize(L + V);

    float s = max(0, dot(N, H));
    s = pow(s, 50);
    float4 specular = s * specularMaterial;

    float4 texcol = g_Tex1.Sample(g_SamplerLinear, input.Tex);
    float4 col = Ambient + specular + diffuse * texcol;
    col.a = texcol.a;
    return col;
}