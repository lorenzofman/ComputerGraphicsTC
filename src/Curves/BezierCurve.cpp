#include "BezierCurve.h"

BezierCurve::BezierCurve() : BezierCurve(Screen::Center(), Bezier::Colors::Curve) { }

BezierCurve::BezierCurve(Float2 center, RGBAFloat color)
{
	AddPoint(center + Float2::Left * 100);
	AddPoint(center + (Float2::Left + Float2::Up) * 50);
	AddPoint(center + (Float2::Right + Float2::Down) * 50);
	AddPoint(center + Float2::Right * 100);
	segmentsCount = 1;
	this->color = color;
}

void BezierCurve::AddSegment(Float2 anchor)
{
	AddPoint(points[points.size() - 1] * 2 - points[points.size() - 2]);
	AddPoint((points[points.size() - 1] + anchor) * 0.5f);
	AddPoint(anchor);
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
	for (auto&& btn : buttons)
	{
		RGBAFloat color = Bezier::Colors::Anchor * (btn->IsMouseOver() ? 0.7f : 1.0f);
		btn->shape->Draw(color);
	}
}

void BezierCurve::OnButtonDrag(Button* button)
{
	int idx = GetButtonIndex(button);
	points[idx] += EventSystem::MousePositionDelta;
	button->shape->Translate(EventSystem::MousePositionDelta);
}

int BezierCurve::GetButtonIndex(Button* button)
{
	for (uint i = 0; i < buttons.size(); i++)
	{
		if (buttons[i] == button)
		{
			return (int) i;
		}
	}
	return -1;
}

void BezierCurve::AddPoint(Float2 point)
{
	points.push_back(point);
	Button* btn = new Button(Bezier::Colors::Anchor, new Circle(point, Bezier::AnchorButtonSize));
	buttons.push_back(btn);
	btn->DragCallback.Register([this](Button* dragBtn) {this->OnButtonDrag(dragBtn); });
}

void BezierCurve::DrawBezierSegment(Float2 a, Float2 b, Float2 c, Float2 d)
{
	Canvas2D::SetColor(color);
	for (float f = 0.0f; f <= 1.0f; f += 0.01f)
	{
		Float2 point = Interpolation::Cubic(a, b, c, d, f);
		Canvas2D::DrawFilledCircle(point, 8, 8);
	}
}
