#include "Canvas2DExtensions.h"

void Canvas2DExtensions::DrawThickLine(Float2 start, Float2 end, RGBAFloat color, float thickness)
{
	Canvas2D::SetColor(color);
	Float2* points = new Float2[4];
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	Float2 direction = Float2(dx, dy);
	Float2 cwDir = direction.PerpendicularClockwise().GetNormalized();
	Float2 ccwDir = direction.PerpendicularCounterClockwise().GetNormalized();

	points[0] = start + cwDir * thickness;
	points[1] = start + ccwDir * thickness;
	points[2] = end + ccwDir * thickness;
	points[3] = end + cwDir * thickness;

	Canvas2D::DrawFilledPolygon(points, 4);
	delete[] points;
}

void Canvas2DExtensions::DrawRoundedRect(Rect rect, RGBAFloat color, float roundness)
{
	Canvas2D::SetColor(color);

	Rect horizontal = rect;
	Rect vertical = rect;
	horizontal.BottomLeft.y += roundness;
	horizontal.TopRight.y -= roundness;

	vertical.BottomLeft.x += roundness;
	vertical.TopRight.x -= roundness;
	int circleSegments = (int) roundness * 2;
	Canvas2D::DrawFilledRect(horizontal.BottomLeft, horizontal.TopRight);
	Canvas2D::DrawFilledRect(vertical.BottomLeft, vertical.TopRight);

	Rect circlesRect = rect;
	Float2 offset = Float2(roundness, roundness);
	circlesRect.BottomLeft += offset;
	circlesRect.BottomRight += Float2(-roundness, roundness);
	circlesRect.TopRight -= offset;
	circlesRect.TopLeft += Float2(roundness, -roundness);
	Canvas2D::DrawFilledCircle(circlesRect.BottomLeft, roundness, circleSegments);
	Canvas2D::DrawFilledCircle(circlesRect.BottomRight, roundness, circleSegments);
	Canvas2D::DrawFilledCircle(circlesRect.TopRight, roundness, circleSegments);
	Canvas2D::DrawFilledCircle(circlesRect.TopLeft, roundness, circleSegments);

}

void Canvas2DExtensions::DrawDashedLine(Float2 start, Float2 end, float dash, float space)
{
	Float2 dir = end - start;
	float length = dir.GetLength();
	int segments = (int) (length / (dash + space));
	float step = 0;
	for (int i = 0; i < segments; i++)
	{
		float t0 = step / length;
		float t1 = (step + dash) / length;
		Canvas2D::DrawLine(Interpolation::Linear(start, end, t0), Interpolation::Linear(start, end, t1));
		step += dash + space;
	}
}
