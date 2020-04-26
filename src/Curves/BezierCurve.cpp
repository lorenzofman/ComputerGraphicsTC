#include "BezierCurve.h"

BezierCurve::BezierCurve() : BezierCurve(Screen::Center(), Colors::BezierCurveDefault) { }

BezierCurve::BezierCurve(Float2 center, RGBAFloat color)
{
	points.push_back(center + Float2::Left * 100);
	points.push_back(center + (Float2::Left + Float2::Up) * 50);
	points.push_back(center + (Float2::Right + Float2::Down) * 50);
	points.push_back(center + Float2::Right * 100);
	segmentsCount = 1;
	this->color = color;
}

void BezierCurve::AddSegment(Float2 anchor)
{
	points.push_back(points[points.size() - 1] * 2 - points[points.size() - 2]);
	points.push_back((points[points.size() - 1] + anchor) * 0.5f);
	points.push_back(anchor);
	segmentsCount++;
}

void BezierCurve::Render()
{
	for (int i = 0; i < segmentsCount; i++)
	{
		DrawBezierSegment(
			points[i * 3 + 0],
			points[i * 3 + 1],
			points[i * 3 + 2],
			points[i * 3 + 3]);
	}
}

void BezierCurve::DrawBezierSegment(Float2 a, Float2 b, Float2 c, Float2 d)
{
	for (float f = 0.0f; f <= 1.0f; f += 0.001f)
	{
		Float2 point = Interpolation::Cubic(a, b, c, d, f);
		Canvas2D::DrawPoint((int)point.x, (int)point.y);
		//Canvas2D::DrawCircle(point, 8, 4);
	}
}
