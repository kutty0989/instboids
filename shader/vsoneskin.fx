//--------------------------------------------------------------------------------------
// vs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// ���_�V�F�[�_�[
//--------------------------------------------------------------------------------------
VS_OUTPUT main(
	float4 Pos		:	POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD,
	int4   BoneIndex : BONEINDEX,
	float4 BoneWeight : BONEWEIGHT
	)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	// ���_�u�����h�̏���
	float4x4 comb = (float4x4)0;
	for (int i = 0; i < 4; i++)
	{
		comb += BoneMatrix[BoneIndex[i]] * BoneWeight[i];
	}

	output.Pos = mul(Pos, comb);

	output.Pos = mul(output.Pos, World);
	output.WPos = output.Pos;
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	float4 N = Normal;
	N.w = 0.0f;					// �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B

	N = mul(N, comb);			// �@���x�N�g���ɃR���r�l�[�V�����s����|���ĕ�����ς���
	N = mul(N, World);			// �@���x�N�g���Ƀ��[���h�ϊ��s����|���ĕ�����ς���
	N = normalize(N);			// ���K��

	output.Normal = N;

	float4 L = LightDirection;
	L = normalize(L);
	L.w = 0.0f;

	float d;
	d = max(0.0f, dot(L, N));	// �����o�[�g�̗]�����ŉA�e��t����

	float4 diffuse;
	diffuse = d;

	output.Tex = Tex;

	output.Color = diffuse;
	return output;
}