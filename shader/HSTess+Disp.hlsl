#include	"psvscommon.hlsl"




HS_CONSTANT_OUTPUT HSConstant(InputPatch<VS_OUTPUT, 3> ip, uint pid : SV_PrimitiveID)
{
    HS_CONSTANT_OUTPUT Out;
   

    Out.factor[0] = tessellationAmount;
    Out.factor[1] = tessellationAmount;
    Out.factor[2] = tessellationAmount;
   
    
    Out.inner_factor = tessellationAmount; //u 縦の分割数（横のラインを何本ひくか）


    return Out;
}
//
//
//
[domain("tri")]//60
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("HSConstant")]
HS_OUTPUT main(InputPatch<VS_OUTPUT, 3> ip, uint cpid : SV_OutputControlPointID, uint pid : SV_PrimitiveID)
{
    HS_OUTPUT Out;
    Out.Pos = ip[cpid].Pos;
   
    Out.color = ip[cpid].Color;
    
    Out.uv = ip[cpid].Tex;
    
    return Out;
}
//
//
//