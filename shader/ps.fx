//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
	float4 col;
	float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
    col = texcol; //* input.Color;
	col.a = 1.0f;
	col.r = 1.0f;
	return col;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 col;
    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
    col = texcol; //* input.Color;
    col = (1.0f, 0.0f, 0.0f, 1.0f);
    return col;
}