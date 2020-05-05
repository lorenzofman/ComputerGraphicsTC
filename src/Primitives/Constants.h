#pragma once

#include "RGBAFloat.h"
#include "Types.h"

namespace Colors
{
	static const RGBAFloat Background = RGBAFloat(0.15f, 0.15f, 0.15f);
}

namespace Bezier
{
	const int AnchorButtonSize = 16;
	const int TangentButtonSize = 8;
	const float AnimationDurationPerSegment = 2;

	namespace Colors
	{
		static const RGBAFloat Curve = RGBAFloat(0.15f, 0.85f, 0.15f);
		static const RGBAFloat Anchor = RGBAFloat(0.85f, 0.15f, 0.15f);
		static const RGBAFloat TangentPoint = RGBAFloat(0.85f, 0.85f, 0.85f);
		static const RGBAFloat TangentLine = RGBAFloat(0, 0, 0);
		static const RGBAFloat DashedLine = RGBAFloat(0.91f, 0.23f, 0.32f);

		static const RGBAFloat BlendingFunctionColors[] = 
		{
			RGBAFloat(0.721f, 0.207f, 0.392f),
			RGBAFloat(1.000f, 0.403f, 0.352f),
			RGBAFloat(1.000f, 0.701f, 0.313f),
			RGBAFloat(0.513f, 0.721f, 0.666f),
		};

		namespace Construction
		{
			static const RGBAFloat Linear = RGBAFloat(0.7f, 0.7f, 0.7f);
			static const RGBAFloat Quadratic = RGBAFloat(0, 0.8f, 0.8f);
			static const RGBAFloat Cubic = RGBAFloat(0.2f, 1.0f, 0.4f);
		}
	}
}

constexpr float PI = 3.14159265359f;