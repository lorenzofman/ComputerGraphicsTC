#pragma once

#include "RGBAFloat.h"
#include "Types.h"

const int TargetFramesPerSeconds = 60;

namespace Colors
{
	static const RGBAFloat Background = RGBAFloat(0.15f, 0.15f, 0.15f);
}

namespace Bezier
{
	const int AnchorButtonSize = 16;
	const int TangentButtonSize = 8;
	const float AnimationDurationPerSegment = 1;
	namespace Colors
	{
		static const RGBAFloat Curve = RGBAFloat(0.15f, 0.85f, 0.15f);
		static const RGBAFloat Anchor = RGBAFloat(0.85f, 0.15f, 0.15f);
		static const RGBAFloat TangentPoint = RGBAFloat(0.85f, 0.85f, 0.85f);
		static const RGBAFloat TangentLine = RGBAFloat(0, 0, 0);
	}
}


constexpr float PI = 3.14159265359f;