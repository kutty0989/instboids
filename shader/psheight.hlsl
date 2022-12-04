//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
    float4 tex1col = g_Tex1.Sample(g_SamplerLinear, input.Tex);
    float4 tex2col = g_Tex2.Sample(g_SamplerLinear, input.Tex);
    float4 tex3col = g_Tex3.Sample(g_SamplerLinear, input.Tex);
    float4 tex4col = g_Tex4.Sample(g_SamplerLinear, input.Tex);
   // float4 tex5col = g_Tex5.Sample(g_SamplerLinear, input.Tex*10.0f);
  
    float arpha = tex1col.r - 0.5f;
    float sarpha = (1 - tex1col.r) - 0.5f;
    float garpha = tex1col.r;
    tex1col.a = 1.0f;
    float4 col = tex1col;
    if (gcol >= 1.0f)
    {
        col = tex2col;
    }
    if(gcol>=2.0f)
    {
       sarpha *= 2.0f;
        if (sarpha < 0)
        {
            sarpha = 0;
        }
            col = tex2col * (1 - sarpha) + tex3col * (sarpha);
    }
    if(gcol >= 3.0f)
    {
        arpha *= 2.0f;
        if (arpha < 0)
        {
            arpha = 0;
        }
        col = col * (1 - arpha) + tex4col * (arpha); //上の地面
    }
   // col = col + tex5col * garpha;
    
    float4 lastcol = col;
    
     return lastcol;
}