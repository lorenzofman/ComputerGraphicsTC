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
	Canvas2D::DrawFilledRect((int) horizontal.BottomLeft.x, (int) horizontal.BottomLeft.y, (int) horizontal.TopRight.x, (int) horizontal.TopRight.y);
	Canvas2D::DrawFilledRect((int) vertical.BottomLeft.x, (int) vertical.BottomLeft.y, (int) vertical.TopRight.x, (int) vertical.TopRight.y);
	
	Rect circlesRect = rect;
	Float2 offset = Float2(roundness, roundness);
	circlesRect.BottomLeft += offset;
	circlesRect.TopRight -= offset;
	Canvas2D::DrawFilledCircle(circlesRect.BottomLeft, roundness, circleSegments);
	Canvas2D::DrawFilledCircle(circlesRect.BottomRight, roundness, circleSegments);
	Canvas2D::DrawFilledCircle(circlesRect.TopRight, roundness, circleSegments);
	Canvas2D::DrawFilledCircle(circlesRect.TopLeft, roundness, circleSegments);

}
