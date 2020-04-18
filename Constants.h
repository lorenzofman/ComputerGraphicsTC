#pragma once

#include "RGBAFloat.h"
namespace Colors 
{
	static const RGBAFloat White = RGBAFloat(1, 1, 1);
	static const RGBAFloat Red = RGBAFloat(1, 0, 0);
	static const RGBAFloat Blue = RGBAFloat(0, 0, 1);
	static const RGBAFloat Green = RGBAFloat(0, 1, 0);
	static const RGBAFloat Yellow = RGBAFloat(1, 0, 0);
	static const RGBAFloat Pink = RGBAFloat(1, 0, 1);
	static const RGBAFloat Black = RGBAFloat(0, 0, 0);
	static const RGBAFloat Blank = RGBAFloat(0, 0, 0, 0);

	static const RGBAFloat Background = RGBAFloat(0.15f, 0.15f, 0.15f);
	static const RGBAFloat Selection = RGBAFloat(0.18f, 0.43f, 0.83f);

	static const RGBAFloat Default = White * 0.9f;

	namespace Google
	{
		static const RGBAFloat Blue = RGBAFloat(0.259f, 0.522f, 0.957f);
		static const RGBAFloat Red = RGBAFloat(0.859f, 0.267f, 0.216f);
		static const RGBAFloat Yellow = RGBAFloat(0.957f, 0.706f, 0.000f);
		static const RGBAFloat Green = RGBAFloat(0.059f, 0.616f, 0.345f);
	}

	namespace Palette
	{
		constexpr int Width = 8;
		constexpr int Height = 4;
		constexpr int ButtonHalfSize = 16;
		constexpr int ColorHeight = 16;
		constexpr int ColorWidth = 21;
		//const RGBAFloat Colors[] = { Google::Blue, Google::Green, Google::Red, Google::Yellow };
		const RGBAFloat Colors[] =
		{
			RGBAFloat(1.000f, 1.000f, 1.000f),
			RGBAFloat(0.898f, 0.898f, 0.898f),
			RGBAFloat(0.800f, 0.800f, 0.800f),
			RGBAFloat(0.698f, 0.698f, 0.698f),
			RGBAFloat(0.600f, 0.600f, 0.600f),
			RGBAFloat(0.400f, 0.400f, 0.400f),
			RGBAFloat(0.200f, 0.200f, 0.200f),
			RGBAFloat(0.000f, 0.000f, 0.000f),

			RGBAFloat(0.820f, 0.737f, 0.824f),
			RGBAFloat(0.976f, 0.824f, 0.871f),
			RGBAFloat(1.000f, 0.733f, 0.694f),
			RGBAFloat(1.000f, 0.859f, 0.663f),
			RGBAFloat(1.000f, 0.859f, 0.663f),
			RGBAFloat(0.780f, 0.910f, 0.675f),
			RGBAFloat(0.600f, 0.835f, 0.792f),
			RGBAFloat(0.698f, 0.839f, 0.937f),

			RGBAFloat(0.702f, 0.569f, 0.710f),
			RGBAFloat(0.961f, 0.710f, 0.784f),
			RGBAFloat(1.000f, 0.561f, 0.502f),
			RGBAFloat(1.000f, 0.765f, 0.455f),
			RGBAFloat(1.000f, 0.875f, 0.443f),
			RGBAFloat(0.639f, 0.851f, 0.467f),
			RGBAFloat(0.353f, 0.729f, 0.655f),
			RGBAFloat(0.514f, 0.733f, 0.898f),

			RGBAFloat(0.514f, 0.255f, 0.529f),
			RGBAFloat(0.871f, 0.373f, 0.522f),
			RGBAFloat(0.788f, 0.176f, 0.224f),
			RGBAFloat(0.937f, 0.553f, 0.133f),
			RGBAFloat(0.988f, 0.769f, 0.220f),
			RGBAFloat(0.478f, 0.714f, 0.282f),
			RGBAFloat(0.098f, 0.588f, 0.490f),
			RGBAFloat(0.047f, 0.486f, 0.729f)
		};
	}
}

constexpr float PI = 3.14159265359f;
constexpr int SelectionThickness = 1;
constexpr int TransfomerEdgeHalfSize = 4;
constexpr int TransformerSideHalfSize = 3;
constexpr float OutlineScrollSpeed = 0.01f;