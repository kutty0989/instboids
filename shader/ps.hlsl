//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"



//float CalcdiffuseFromFresnel(float3 N,float L,float V)
//{
//	//�@���ƌ����Ɍ������x�N�g�����ǂꂾ�����Ă��邩���Ȃ��Ȃŋ��߂�
//    float dotNL = saturate(dot(N, L));
	
//	//�@���Ǝ����Ɍ������x�N�g�����ǂꂾ�����Ă��邩����ςŋ��߂�
//    float dotNV = saturate(dot(N, V));

//	//�@���ƌ����ւ̕����Ɉˑ�����g�U���˗��ƁA�@���Ǝ����x�N�g���Ɉˑ�����g�U���˗���
//	//��Z���čŏI�I�Ȋg�U���˗������Ƃ߂�
//    return (dotNL * dotNV);
	
//}

//// �x�b�N�}�����z���v�Z����
//float Beckmann(float m, float t)
//{
//    float t2 = t * t;
//    float t4 = t * t * t * t;
//    float m2 = m * m;
//    float D = 1.0f / (4.0f * m2 * t4);
//    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
//    return D;
//}

//// �t���l�����v�Z�BSchlick�ߎ����g�p
//float SpcFresnel(float f0, float u)
//{
//    // from Schlick
//    return f0 + (1 - f0) * pow(1 - u, 5);
//}

//float CookTorranceSpecular(float3 L, float3 V, float3 N, float metallic)
//{
//    float microfacet = 0.76f;

//    // �����x�𐂒����˂̎��̃t���l�����˗��Ƃ��Ĉ���
//    // �����x�������قǃt���l�����˂͑傫���Ȃ�
//    float f0 = metallic;

//    // ���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
//    float3 H = normalize(L + V);

//    // �e��x�N�g�����ǂꂭ�炢���Ă��邩����ς𗘗p���ċ��߂�
//    float NdotH = saturate(dot(N, H));
//    float VdotH = saturate(dot(V, H));
//    float NdotL = saturate(dot(N, L));
//    float NdotV = saturate(dot(N, V));

//    // D�����x�b�N�}�����z��p���Čv�Z����
//    float D = Beckmann(microfacet, NdotH);

//    // F����Schlick�ߎ���p���Čv�Z����
//    float F = SpcFresnel(f0, VdotH);

//    // G�������߂�
//    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

//    // m�������߂�
//    float m = 3.141592f * NdotV * NdotH;

//    // �����܂ŋ��߂��A�l�𗘗p���āACook-Torrance���f���̋��ʔ��˂����߂�
//    return max(F * D * G / m, 0.0);
//}
//--------------------------------------------------------------------------------------
//  �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------
//float4 main(VS_OUTPUT input) : SV_Target
//{
	
//	float4 N = input.Normal;
//	float4 L = LightDirection;
//	N.w = 0.0f;					// �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B
//	L.w = 0.0f;					// ���̕����̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B
    
//	//�e��}�b�v���T���v�����O
//	//�A���x�h�J���[�i�g�U���ˌ��j
//    float4 albedoColor = g_albedo.Sample(g_SamplerLinear, input.Tex);
	
    
//	//�X�y�L�����[�̓A���x�h�J���[�Ɠ����ɂ���
//    float3 specColor = albedoColor;
	
//	//�����x
//    float metalic = g_metallicSmoothMap.Sample(g_SamplerLinear, input.Tex).r;
	
//	//���炩��
//    float smooth = g_metallicSmoothMap.Sample(g_SamplerLinear, input.Tex).a;
	
   
//	//�����Ɍ������Ă̂т�x�N�g���v�Z
//    float3 toEye = normalize(EyePos - input.WPos);
	
//    float3 lig = 0;
	

//		//�t���l�����˂��l�������g�U���˂��v�Z
//    float diffuseFromFrenel = CalcdiffuseFromFresnel(N.xyz, -L.x, toEye.x);
		
//		//���K��Lambert�g�U���˂����߂�
//    float NdotL = saturate(dot(N ,-L));
//    float3 lambertDiffuse = L * NdotL / 3.14159265f;
    
//		//�ŏI�I�Ȋg�U���ˌ����v�Z
//    float3 diffuse = albedoColor.rgb * diffuseFromFrenel * lambertDiffuse;
	
//	//Cool_Torrance���f���̋��ʔ��˗����v�Z����
//    float3 spec = CookTorranceSpecular(-L.xyz, toEye, N.xyz, smooth) * L;
	
//	//�����x��������΁A���ʔ��˂̓X�y�L�����J���[�A�Ⴏ��Δ�
//	//�X�y�L�����[�J���[�̋��������ʔ��˗��Ƃ��Ĉ���
//    spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metalic);
	
//	//���炩�����g���Ċg�U���ˌ��Ƌ��ʔ��ˌ�����������
//	//���炩����������΁A���ʔ��˂͎キ�Ȃ�
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
   
	
	

//    // �����ɂ���グ
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
    N.w = 0.0f; // �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B
    L.w = 0.0f; // ���̕����̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B

    N = normalize(N);
    L = normalize(L);

    float d = max(0.0, dot(L, N)); //�s�p���݊p���𒲂ׂ�@90�x��
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