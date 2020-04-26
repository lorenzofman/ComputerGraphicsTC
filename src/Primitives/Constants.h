#pragma once

#include "RGBAFloat.h"
#include "Types.h"
namespace Colors
{
	static const RGBAFloat Background = RGBAFloat(0.15f, 0.15f, 0.15f);
}

namespace Bezier
{
	const int AnchorButtonSize = 10;
	const int TangentButtonSize = 7;
	namespace Colors
	{
		static const RGBAFloat Curve = RGBAFloat(0.15f, 0.85f, 0.15f);
		static const RGBAFloat Anchor = RGBAFloat(0.85f, 0.15f, 0.15f);
		static const RGBAFloat BezierTangent = RGBAFloat(0.85f, 0.85f, 0.85f);
	}
}


constexpr float PI = 3.14159265359f;