DXBCъl№ЛH•/ZHz(пУYfь   †;     8   D  Ш  р  ь  Ш  RDEF     l      <    ю€	  №  RD11<          (   $          \                             ConstantBuffer Ђ\      Д   0           d            p      €€€€    €€€€    Ф           p      €€€€    €€€€    Щ           p      €€€€    €€€€    Я           p      €€€€    €€€€    •           p      €€€€    €€€€    Ђ           p      €€€€    €€€€    ±            p      €€€€    €€€€    Є            p      €€€€    €€€€    њ             p      €€€€    €€€€    ∆  $         p      €€€€    €€€€    Ќ  (         p      €€€€    €€€€    ‘  ,          p      €€€€    €€€€    posX float Ђ                             i  posY fontX fontY fontW fontH colorR colorG colorB scaleX scaleY useless Microsoft (R) HLSL Shader Compiler 10.1 ISGNL         8                    A                   POSITION TEXCOORD ЂЂOSGNP         8                    D                   SV_POSITION TEXCOORD ЂЂЂSHEX  P  A   j Y  FО         _  т     _  2    g  т         e  2     h        
т      F     @    А?  А?        8  
¬      ¶     @                А?2  2      F      ЦЕ         FА          2  2     F    FА         жК          >  STATФ                                                                                                                                                  SPDB 6  Microsoft C/C++ MSF 7.00
DS            Р                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ј€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€8  ь€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€       <       €€€€                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         Ф.1)/B_   .уУсГщыNФ7AйЯ≥                          №Q3                                                                                                                                                                                                                                                                                                                                                                                                                                                                    TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	input.Pos.xy = input.Pos.xy + float2(1.0, 1.0);
	output.Pos = float4(posX, posY, 0.0, 0.0) + input.Pos * float4(scaleX, scaleY, 0.0, 1.0) ;
	output.Tex = float2(fontX, fontY) + input.Tex * float2(fontW, fontH) ;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 clr = Texture.Sample(LinearBorder, input.Tex);
	clr.a =∆Z  uГ Ь' Ь  &ч Eg  m ш" Тж ж                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
Texture2D Texture : register(t0);

SamplerState LinearBorder : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	float posX;
	float posY;
	float fontX;
	float fontY;
	float fontW;
	float fontH;
	float colorR;
	float colorG;
	float colorB;
	float scaleX;
	float scaleY;
	float useless;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	input.Pos.xy = input.Pos.xy + float2(1.0, 1.0);
	output.Pos = float4(posX, posY, 0.0, 0.0) + input.Pos * float4(scaleX, scaleY, 0.0, 1.0) ;
	output.Tex = float2(fontX, fontY) + input.Tex * float2(fontW, fontH) ;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 clr = Texture.Sample(LinearBorder, input.Tex);
	clr.a = saturate(clr.x + clr.y + clr.z);
	clr.xyz = clr.xyz * float3(colorR, colorG, colorB);
	
	return clr;
}                             юпюп   `   D:\Desktop\Programs\DirectxEngine\Dx11Project\shader\Font.fx  d:\desktop\programs\directxengine\dx11project\shader\font.fx 
Texture2D Texture : register(t0);

SamplerState LinearBorder : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	float posX;
	float posY;
	float fontX;
	float fontY;
	float fontW;
	float fontH;
	float colorR;
	float colorG;
	float colorB;
	float scaleX;
	float scaleY;
	float useless;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : в0А   Ђ®≠>+y÷                                                               ?   (   в0gx«Ќг     >   ?                                                                                                                                                                                                                                                                                                                                                                                                                  B <   
   ЇG
   ЇGMicrosoft (R) HLSL Shader Compiler 10.1   6 =hlslFlags 0x801 hlslTarget vs_5_0 hlslEntry VS     *     8      ђ       ђ     X    †VS   . >  	 input                                  P     X    ђ      P    X    ђ     P    X    ђ     P    X    ђ     P    X    ђ     P    X    ђ    : >  И <VS return value>                                  P    X    ђ     P    X    ђ     P     X    ђ      P    X    ђ     P    X    ђ     P    X    ђ      ф         	€Ќл«йцѓеU[  т   Р               
   Д   X   &  АX   &   А   &  АА   &   ®   &  А®   &   ‘   '  А‘   '      (  А   (    [ . Y  [ . Y  [  Y  G  E     ц          $          0   L   h   Д   †   Љ   Ў                                                                                                                                                                                                                            18      
  ‘   
 €€   €€     (   (      0        @       float4 утс @       float2 утс"       Pos тс    Tex тс               VS_INPUT с
                     VS_OUTPUT 
            
 @     
                                                                                                                                                                                                                                                          18              €€   €€                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  saturate(clr.x + clr.y + clr.z);
	clr.xyz = clr.xyz * float3(colorR, colorG, colorB);
	
	return clr;
}        >          ?       |                                                                                                                                                                                                                                                                                                                                                                                      D3DSHDR                              `                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        €€€€	/сH   (  °      i      M      Е            1            ў      љ                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              $   0   <   H   T   `                                                                                                                                                                                                                                                                                                                                                                                                    %    А    VS     Q	       €€€€€€posX     Q	      €€€€€€posY     Q	      €€€€€€fontX    Q	      €€€€€€fontY    Q	      €€€€€€fontW    Q	      €€€€€€fontH    Q	     $ €€€€€€scaleX   Q	     ( €€€€€€scaleY                                                                                                                                                                                                                                                                                                         €€€€	/с                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            Ф.1)/B_   .уУсГщыNФ7AйЯ≥j   /LinkInfo /names /src/headerblock /src/files/d:\desktop\programs\directxengine\dx11project\shader\font.fx          :             
             "          №Q3                                                                                                                                                                                                                                                                                                                          €€€€w	1     О ?\   H       ,   L                                         `             	 <      ƒ                  VS none -Ї.с            `                    €€€€            €€€€    €€€€         D:\Desktop\Programs\DirectxEngine\Dx11Project\shader\Font.fx    юпюп                  €€€€€€€€€€ €€€€€€€€€€                                                                                                                                                                                        ∆     O  8       Р  А   г  (  0       (   А  ,   ф                  
               	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          