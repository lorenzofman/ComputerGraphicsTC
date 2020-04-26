#pragma once

#include <vector>

#include "../Interfaces/IRenderable.h"
#include "../Primitives/Float2.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Constants.h"
#include "../DataStructures/Array.h"
#include "../Helpers/Interpolation.h"
#include "../Canvas2D/Canvas2D.h"
#include "../World/Screen.h"

class BezierCurve : public IRenderable
{
	public:
	BezierCurve();
	BezierCurve(Float2 start, RGBAFloat color);
	void AddSegment(Float2 point);
	virtual void Render() override;
	private:
	std::vector<Float2> points = std::vector<Float2>();
	int segmentsCount;
	RGBAFloat color;
	void DrawBezierSegment(Float2 a, Float2 b, Float2 c, Float2 d);
};

