#ifndef __MYCOLOR_H__
#define __MYCOLOR_H__

#include "Utility/utility.h"
namespace DX11
{
	enum ColorType
	{
		Black,
		DimGray,
		Gray,
		DarkGray,
		Silver,
		LightGray,
		Gainsboro,
		WhiteSmoke,
		White,
		Snow,
		IronGray,
		SandBeige,
		RosyBrown,
		LightCoral,
		IndianRed,
		Brown,
		FireBrick,
		Maroon,
		DarkRed,
		StrongRed,
		Red,
		Persimmon,
		MistyRose,
		Salmon,
		Scarlet,
		Tomato,
		DarkSalmon,
		Coral,
		OrangeRed,
		LightSalmon,
		Vermilion,
		Sienna,
		TropicalOrange,
		Camel,
		Apricot,
		CoconutBrown,
		Seashell,
		SaddleBrown,
		Chocolate,
		BurntOrange,
		SunOrange,
		PeachPuff,
		SandBrown,
		Bronze,
		Linen,
		HoneyOrange,
		Peru,
		Sepia,
		Ocher,
		Bisque,
		Tangerine,
		DarkOrange,
		AntiqueWhite,
		Tan,
		BurlyWood,
		BlanchedAlmond,
		NavajoWhite,
		Marigold,
		PapayaWhip,
		PaleOcre,
		Khaki,
		Moccasin,
		OldLace,
		Wheat,
		Peach,
		Orange,
		FloralWhite,
		Goldenrod,
		DarkGoldenrod,
		Coffee,
		Jasmine,
		Amber,
		Cornsilk,
		ChromeYellow,
		Golden,
		LemonChiffon,
		LightKhaki,
		PaleGoldenrod,
		DarkKhaki,
		Mimosa,
		Cream,
		Ivory,
		Beige,
		LightYellow,
		LightGoldenrodYellow,
		ChampagneYellow,
		Mustard,
		MoonYellow,
		Olive,
		CanaryYellow,
		Yellow,
		MossGreen,
		LightLime,
		OliveDrab,
		YellowGreen,
		DarkOliveGreen,
		AppleGreen,
		GreenYellow,
		GrassGreen,
		LawnGreen,
		Chartreuse,
		FoliageGreen,
		FreshLeaves,
		BrightGreen,
		CobaltGreen,
		Honeydew,
		DarkSeaGreen,
		LightGreen,
		PaleGreen,
		IvyGreen,
		ForestGreen,
		LimeGreen,
		DarkGreen,
		Green,
		Lime,
		Malachite,
		Mint,
		Celadon,
		VeryLightMalachiteGreen,
		TurquoiseGreen,
		Viridian,
		HorizonBlue,
		SeaGreen,
		MediumSeaGreen,
		MintCream,
		SpringGreen,
		PeacockGreen,
		MediumSpringGreen,
		MediumAquamarine,
		Aquamarine,
		CyanBlue,
		AquaBlue,
		TurquoiseBlue,
		Turquoise,
		LightSeaGreen,
		MediumTurquoise,
		LightCyan,
		BabyBlue,
		PaleTurquoise,
		DarkSlateGray,
		Teal,
		DarkCyan,
		Cyan,
		Aqua,
		DarkTurquoise,
		CadetBlue,
		PeacockBlue,
		PowderBlue,
		StrongBlue,
		LightBlue,
		PaleBlue,
		SaxeBlue,
		DeepSkyBlue,
		MarineBlue,
		Prussianblue,
		AliceBlue,
		DodgerBlue,
		MineralBlue,
		Azure,
		WedgwoodBlue,
		LightSteelBlue,
		CobaltBlue,
		PaleDenim,
		SalviaBlue,
		DarkPowderBlue,
		Sapphire,
		InternationalKleinBlue,
		Ceruleanblue,
		RoyalBlue,
		DarkMineralBlue,
		Ultramarine,
		LapisLazuli,
		GhostWhite,
		LavenderMist,
		LavenderBlue,
		Periwinkle,
		MidnightBlue,
		NavyBlue,
		DarkBlue,
		MediumBlue,
		Blue,
		GrayishPurple,
		Indigo,
		DarkSlateBlue,
		SteelBlue,
		Emerald,
		Purple,
		SlateBlue,
		CornflowerBlue,
		MediumSlateBlue,
		Violet,
		SlateGray,
		LightSlateGray,
		BlueViolet,
		DarkMagenta,
		Plum,
		SkyBlue,
		LightSkyBlue,
		Burgundy,
		Patriarch,
		MediumPurple,
		DarkViolet,
		DarkOrchid,
		Amethyst,
		MediumOrchid,
		Lavender,
		Pansy,
		Mallow,
		OperaMauve,
		PailLilac,
		MineralViolet,
		LightViolet,
		Wisteria,
		Lilac,
		MediumLavenderMagenta,
		LavenderMagenta,
		Heliotrope,
		Mauve,
		Thistle,
		Clematis,
		Magenta,
		Fuchsia,
		Orchid,
		PearlPink,
		OldRose,
		RosePink,
		MediumVioletRed,
		MagentaRose,
		Rose,
		Ruby,
		Camellia,
		DeepPink,
		Flamingo,
		CoralPink,
		HotPink,
		SpinelRed,
		Carmine,
		BabyPink,
		CardinalRed,
		LavenderBlush,
		PaleVioletRed,
		Cerise,
		SalmonPink,
		Crimson,
		Pink,
		LightPink,
		ShellPink,
		AlizarinCrimson,

		TotalColor,
	};

	
	namespace _color
	{
		static const MT::float3 g_Colors[ColorType::TotalColor] =
		{
			{ 0.000000f	,	0.0000000f	,	0.0000000f },
			{ 0.411765f	,	0.4117647f	,	0.4117647f },
			{ 0.501961f	,	0.5019608f	,	0.5019608f },
			{ 0.662745f	,	0.6627451f	,	0.6627451f },
			{ 0.752941f	,	0.7529412f	,	0.7529412f },
			{ 0.827451f	,	0.8274510f	,	0.8274510f },
			{ 0.862745f	,	0.8627451f	,	0.8627451f },
			{ 0.960784f	,	0.9607843f	,	0.9607843f },
			{ 1.000000f	,	1.0000000f	,	1.0000000f },
			{ 1.000000f	,	0.9803922f	,	0.9803922f },
			{ 0.384314f	,	0.3568627f	,	0.3411765f },
			{ 0.901961f	,	0.7647059f	,	0.7647059f },
			{ 0.737255f	,	0.5607843f	,	0.5607843f },
			{ 0.941176f	,	0.5019608f	,	0.5019608f },
			{ 0.803922f	,	0.3607843f	,	0.3607843f },
			{ 0.647059f	,	0.1647059f	,	0.1647059f },
			{ 0.698039f	,	0.1333333f	,	0.1333333f },
			{ 0.501961f	,	0.0000000f	,	0.0000000f },
			{ 0.545098f	,	0.0000000f	,	0.0000000f },
			{ 0.901961f	,	0.0000000f	,	0.0000000f },
			{ 1.000000f	,	0.0000000f	,	0.0000000f },
			{ 1.000000f	,	0.3019608f	,	0.2509804f },
			{ 1.000000f	,	0.8941176f	,	0.8823529f },
			{ 0.980392f	,	0.5019608f	,	0.4470588f },
			{ 1.000000f	,	0.1411765f	,	0.0000000f },
			{ 1.000000f	,	0.3882353f	,	0.2784314f },
			{ 0.913725f	,	0.5882353f	,	0.4784314f },
			{ 1.000000f	,	0.4980392f	,	0.3137255f },
			{ 1.000000f	,	0.2705882f	,	0.0000000f },
			{ 1.000000f	,	0.6274510f	,	0.4784314f },
			{ 1.000000f	,	0.3019608f	,	0.0000000f },
			{ 0.627451f	,	0.3215686f	,	0.1764706f },
			{ 1.000000f	,	0.5019608f	,	0.2000000f },
			{ 0.631373f	,	0.4196078f	,	0.2784314f },
			{ 0.901961f	,	0.6000000f	,	0.4000000f },
			{ 0.301961f	,	0.1215686f	,	0.0000000f },
			{ 1.000000f	,	0.9607843f	,	0.9333333f },
			{ 0.545098f	,	0.2705882f	,	0.0745098f },
			{ 0.823529f	,	0.4117647f	,	0.1176471f },
			{ 0.800000f	,	0.3333333f	,	0.0000000f },
			{ 1.000000f	,	0.4509804f	,	0.0000000f },
			{ 1.000000f	,	0.8549020f	,	0.7254902f },
			{ 0.956863f	,	0.6431373f	,	0.3764706f },
			{ 0.721569f	,	0.4509804f	,	0.2000000f },
			{ 0.980392f	,	0.9411765f	,	0.9019608f },
			{ 1.000000f	,	0.7019608f	,	0.4000000f },
			{ 0.803922f	,	0.5215686f	,	0.2470588f },
			{ 0.439216f	,	0.2588235f	,	0.0784314f },
			{ 0.800000f	,	0.4666667f	,	0.1333333f },
			{ 1.000000f	,	0.8941176f	,	0.7686275f },
			{ 0.949020f	,	0.5215686f	,	0.0000000f },
			{ 1.000000f	,	0.5490196f	,	0.0000000f },
			{ 0.980392f	,	0.9215686f	,	0.8431373f },
			{ 0.823529f	,	0.7058824f	,	0.5490196f },
			{ 0.870588f	,	0.7215686f	,	0.5294118f },
			{ 1.000000f	,	0.9215686f	,	0.8039216f },
			{ 1.000000f	,	0.8705882f	,	0.6784314f },
			{ 1.000000f	,	0.6000000f	,	0.0000000f },
			{ 1.000000f	,	0.9372549f	,	0.8352941f },
			{ 0.800000f	,	0.7019608f	,	0.5490196f },
			{ 0.600000f	,	0.4196078f	,	0.1215686f },
			{ 1.000000f	,	0.8941176f	,	0.7098039f },
			{ 0.992157f	,	0.9607843f	,	0.9019608f },
			{ 0.960784f	,	0.8705882f	,	0.7019608f },
			{ 1.000000f	,	0.8980392f	,	0.7058824f },
			{ 1.000000f	,	0.5019608f	,	0.0000000f },
			{ 1.000000f	,	0.9803922f	,	0.9411765f },
			{ 0.854902f	,	0.6470588f	,	0.1254902f },
			{ 0.721569f	,	0.5254902f	,	0.0431373f },
			{ 0.301961f	,	0.2235294f	,	0.0000000f },
			{ 0.901961f	,	0.7647059f	,	0.3607843f },
			{ 1.000000f	,	0.7490196f	,	0.0000000f },
			{ 1.000000f	,	0.9725490f	,	0.8627451f },
			{ 0.901961f	,	0.7215686f	,	0.0000000f },
			{ 1.000000f	,	0.8431373f	,	0.0000000f },
			{ 1.000000f	,	0.9803922f	,	0.8039216f },
			{ 0.941176f	,	0.9019608f	,	0.5490196f },
			{ 0.933333f	,	0.9098039f	,	0.6666667f },
			{ 0.741176f	,	0.7176471f	,	0.4196078f },
			{ 0.901961f	,	0.8509804f	,	0.2000000f },
			{ 1.000000f	,	0.9921569f	,	0.8156863f },
			{ 1.000000f	,	1.0000000f	,	0.9411765f },
			{ 0.960784f	,	0.9607843f	,	0.8627451f },
			{ 1.000000f	,	1.0000000f	,	0.8784314f },
			{ 0.980392f	,	0.9803922f	,	0.8235294f },
			{ 1.000000f	,	1.0000000f	,	0.6000000f },
			{ 0.800000f	,	0.8000000f	,	0.3019608f },
			{ 1.000000f	,	1.0000000f	,	0.3019608f },
			{ 0.501961f	,	0.5019608f	,	0.0000000f },
			{ 1.000000f	,	0.9372549f	,	0.0000000f },
			{ 1.000000f	,	1.0000000f	,	0.0000000f },
			{ 0.411765f	,	0.4666667f	,	0.1372549f },
			{ 0.800000f	,	1.0000000f	,	0.0000000f },
			{ 0.419608f	,	0.5568627f	,	0.1372549f },
			{ 0.603922f	,	0.8039216f	,	0.1960784f },
			{ 0.333333f	,	0.4196078f	,	0.1843137f },
			{ 0.549020f	,	0.9019608f	,	0.0000000f },
			{ 0.678431f	,	1.0000000f	,	0.1843137f },
			{ 0.600000f	,	0.9019608f	,	0.3019608f },
			{ 0.486275f	,	0.9882353f	,	0.0000000f },
			{ 0.498039f	,	1.0000000f	,	0.0000000f },
			{ 0.450980f	,	0.7215686f	,	0.2235294f },
			{ 0.600000f	,	1.0000000f	,	0.3019608f },
			{ 0.400000f	,	1.0000000f	,	0.0000000f },
			{ 0.400000f	,	1.0000000f	,	0.3490196f },
			{ 0.941176f	,	1.0000000f	,	0.9411765f },
			{ 0.560784f	,	0.7372549f	,	0.5607843f },
			{ 0.564706f	,	0.9333333f	,	0.5647059f },
			{ 0.596078f	,	0.9843137f	,	0.5960784f },
			{ 0.211765f	,	0.7490196f	,	0.2117647f },
			{ 0.133333f	,	0.5450980f	,	0.1333333f },
			{ 0.196078f	,	0.8039216f	,	0.1960784f },
			{ 0.000000f	,	0.3921569f	,	0.0000000f },
			{ 0.000000f	,	0.5019608f	,	0.0000000f },
			{ 0.000000f	,	1.0000000f	,	0.0000000f },
			{ 0.133333f	,	0.7647059f	,	0.1803922f },
			{ 0.086275f	,	0.5960784f	,	0.1686275f },
			{ 0.674510f	,	0.8823529f	,	0.6862745f },
			{ 0.450980f	,	0.9019608f	,	0.5490196f },
			{ 0.301961f	,	0.9019608f	,	0.5019608f },
			{ 0.070588f	,	0.4549020f	,	0.2117647f },
			{ 0.721569f	,	0.8666667f	,	0.7843137f },
			{ 0.180392f	,	0.5450980f	,	0.3411765f },
			{ 0.235294f	,	0.7019608f	,	0.4431373f },
			{ 0.960784f	,	1.0000000f	,	0.9803922f },
			{ 0.000000f	,	1.0000000f	,	0.5019608f },
			{ 0.000000f	,	0.6313725f	,	0.3607843f },
			{ 0.000000f	,	0.9803922f	,	0.6039216f },
			{ 0.400000f	,	0.8039216f	,	0.6666667f },
			{ 0.498039f	,	1.0000000f	,	0.8313725f },
			{ 0.050980f	,	0.7490196f	,	0.5490196f },
			{ 0.400000f	,	1.0000000f	,	0.9019608f },
			{ 0.000000f	,	1.0000000f	,	0.9372549f },
			{ 0.266667f	,	0.8784314f	,	0.8156863f },
			{ 0.125490f	,	0.6980392f	,	0.6666667f },
			{ 0.282353f	,	0.8196078f	,	0.8000000f },
			{ 0.878431f	,	1.0000000f	,	1.0000000f },
			{ 0.537255f	,	0.8117647f	,	0.9411765f },
			{ 0.686275f	,	0.9333333f	,	0.9333333f },
			{ 0.184314f	,	0.3098039f	,	0.3098039f },
			{ 0.000000f	,	0.5019608f	,	0.5019608f },
			{ 0.000000f	,	0.5450980f	,	0.5450980f },
			{ 0.000000f	,	1.0000000f	,	1.0000000f },
			{ 0.686275f	,	0.8745098f	,	0.8941176f },
			{ 0.000000f	,	0.8078431f	,	0.8196078f },
			{ 0.372549f	,	0.6196078f	,	0.6274510f },
			{ 0.000000f	,	0.5019608f	,	0.5490196f },
			{ 0.690196f	,	0.8784314f	,	0.9019608f },
			{ 0.000000f	,	0.3882353f	,	0.4549020f },
			{ 0.678431f	,	0.8470588f	,	0.9019608f },
			{ 0.819608f	,	0.9294118f	,	0.9490196f },
			{ 0.278431f	,	0.5960784f	,	0.7019608f },
			{ 0.000000f	,	0.7490196f	,	1.0000000f },
			{ 0.000000f	,	0.2784314f	,	0.4901961f },
			{ 0.000000f	,	0.1921569f	,	0.3254902f },
			{ 0.941176f	,	0.9725490f	,	1.0000000f },
			{ 0.117647f	,	0.5647059f	,	1.0000000f },
			{ 0.000000f	,	0.3019608f	,	0.6000000f },
			{ 0.000000f	,	0.4980392f	,	1.0000000f },
			{ 0.337255f	,	0.5254902f	,	0.7490196f },
			{ 0.690196f	,	0.7686275f	,	0.8705882f },
			{ 0.000000f	,	0.2784314f	,	0.6705882f },
			{ 0.368627f	,	0.5254902f	,	0.7568627f },
			{ 0.301961f	,	0.5019608f	,	0.9019608f },
			{ 0.000000f	,	0.2000000f	,	0.6000000f },
			{ 0.031373f	,	0.1450980f	,	0.4039216f },
			{ 0.000000f	,	0.1843137f	,	0.6549020f },
			{ 0.164706f	,	0.3215686f	,	0.7450980f },
			{ 0.254902f	,	0.4117647f	,	0.8823529f },
			{ 0.141176f	,	0.2117647f	,	0.4901961f },
			{ 0.000000f	,	0.2000000f	,	1.0000000f },
			{ 0.149020f	,	0.3803922f	,	0.6117647f },
			{ 0.972549f	,	0.9725490f	,	1.0000000f },
			{ 0.901961f	,	0.9019608f	,	0.9803922f },
			{ 0.800000f	,	0.8000000f	,	1.0000000f },
			{ 0.764706f	,	0.8039216f	,	0.9019608f },
			{ 0.098039f	,	0.0980392f	,	0.4392157f },
			{ 0.000000f	,	0.0000000f	,	0.5019608f },
			{ 0.000000f	,	0.0000000f	,	0.5450980f },
			{ 0.000000f	,	0.0000000f	,	0.8039216f },
			{ 0.000000f	,	0.0000000f	,	1.0000000f },
			{ 0.525490f	,	0.4549020f	,	0.6313725f },
			{ 0.294118f	,	0.0000000f	,	0.5019608f },
			{ 0.282353f	,	0.2392157f	,	0.5450980f },
			{ 0.274510f	,	0.5098039f	,	0.7058824f },
			{ 0.313725f	,	0.7843137f	,	0.4705882f },
			{ 0.415686f	,	0.0509804f	,	0.6784314f },
			{ 0.415686f	,	0.3529412f	,	0.8039216f },
			{ 0.392157f	,	0.5843137f	,	0.9294118f },
			{ 0.482353f	,	0.4078431f	,	0.9333333f },
			{ 0.498039f	,	0.0000000f	,	1.0000000f },
			{ 0.439216f	,	0.5019608f	,	0.5647059f },
			{ 0.466667f	,	0.5333333f	,	0.6000000f },
			{ 0.541176f	,	0.1686275f	,	0.8862745f },
			{ 0.545098f	,	0.0000000f	,	0.5450980f },
			{ 0.556863f	,	0.2705882f	,	0.5215686f },
			{ 0.529412f	,	0.8078431f	,	0.9215686f },
			{ 0.529412f	,	0.8078431f	,	0.9803922f },
			{ 0.501961f	,	0.0000000f	,	0.1254902f },
			{ 0.501961f	,	0.0000000f	,	0.5019608f },
			{ 0.576471f	,	0.4392157f	,	0.8588235f },
			{ 0.580392f	,	0.0000000f	,	0.8274510f },
			{ 0.600000f	,	0.1960784f	,	0.8000000f },
			{ 0.600000f	,	0.4000000f	,	0.8000000f },
			{ 0.729412f	,	0.3333333f	,	0.8274510f },
			{ 0.709804f	,	0.4941176f	,	0.8627451f },
			{ 0.454902f	,	0.0000000f	,	0.6313725f },
			{ 0.850980f	,	0.3019608f	,	1.0000000f },
			{ 0.717647f	,	0.5176471f	,	0.6549020f },
			{ 0.901961f	,	0.8117647f	,	0.9019608f },
			{ 0.639216f	,	0.6156863f	,	0.6823529f },
			{ 0.690196f	,	0.6156863f	,	0.7254902f },
			{ 0.788235f	,	0.6274510f	,	0.8627451f },
			{ 0.784314f	,	0.6352941f	,	0.7843137f },
			{ 0.866667f	,	0.6274510f	,	0.8666667f },
			{ 0.933333f	,	0.5098039f	,	0.9333333f },
			{ 0.874510f	,	0.4509804f	,	1.0000000f },
			{ 0.878431f	,	0.6901961f	,	1.0000000f },
			{ 0.847059f	,	0.7490196f	,	0.8470588f },
			{ 0.800000f	,	0.6392157f	,	0.8000000f },
			{ 1.000000f	,	0.0000000f	,	1.0000000f },
			{ 0.956863f	,	0.0000000f	,	0.6313725f },
			{ 0.854902f	,	0.4392157f	,	0.8392157f },
			{ 1.000000f	,	0.7019608f	,	0.9019608f },
			{ 0.752941f	,	0.5019608f	,	0.5058824f },
			{ 1.000000f	,	0.4000000f	,	0.8000000f },
			{ 0.780392f	,	0.0823529f	,	0.5215686f },
			{ 1.000000f	,	0.0509804f	,	0.6509804f },
			{ 1.000000f	,	0.0000000f	,	0.4980392f },
			{ 0.800000f	,	0.0000000f	,	0.5019608f },
			{ 0.901961f	,	0.2235294f	,	0.5843137f },
			{ 1.000000f	,	0.0784314f	,	0.5764706f },
			{ 0.901961f	,	0.5411765f	,	0.7215686f },
			{ 1.000000f	,	0.5019608f	,	0.7490196f },
			{ 1.000000f	,	0.4117647f	,	0.7058824f },
			{ 1.000000f	,	0.4509804f	,	0.7019608f },
			{ 0.901961f	,	0.0000000f	,	0.3607843f },
			{ 1.000000f	,	0.8509804f	,	0.9019608f },
			{ 0.600000f	,	0.0000000f	,	0.2117647f },
			{ 1.000000f	,	0.9411765f	,	0.9607843f },
			{ 0.858824f	,	0.4392157f	,	0.5764706f },
			{ 0.870588f	,	0.1921569f	,	0.3882353f },
			{ 1.000000f	,	0.5019608f	,	0.6000000f },
			{ 0.862745f	,	0.0784314f	,	0.2352941f },
			{ 1.000000f	,	0.7529412f	,	0.7960784f },
			{ 1.000000f	,	0.7137255f	,	0.7568627f },
			{ 1.000000f	,	0.7019608f	,	0.7490196f },
			{ 0.890196f	,	0.1490196f	,	0.2117647f },
		};
	}

	class Color
	{
	public:
		static MT::float3 *Get(ColorType pType) 
		{
			return  (MT::float3*)&_color::g_Colors[pType];
		}
	protected:
	private:
	};

	

}

#endif