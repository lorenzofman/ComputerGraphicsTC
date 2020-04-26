#include "BezierCurve.h"

BezierCurve::BezierCurve() : BezierCurve(Screen::Center(), Bezier::Colors::Curve) { }

BezierCurve::BezierCurve(Float2 center, RGBAFloat color)
{
	AddPoint(center + Float2::Left * 100, true);
	AddPoint(center + (Float2::Left + Float2::Up) * 50, false);
	AddPoint(center + (Float2::Right + Float2::Down) * 50, false);
	AddPoint(center + Float2::Right * 100, true);
	segmentsCount = 1;
	this->color = color;
	EventSystem::LeftMouseButtonDownCallback.Register([this] {this->OnMouseClick(); });
}

void BezierCurve::AddSegment(Float2 anchor)
{
	AddPoint(points[points.size() - 1] * 2 - points[points.size() - 2], false);
	AddPoint((points[points.size() - 1] + anchor) * 0.5f, false);
	AddPoint(anchor, true);
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
		Canvas2D::SetColor(Bezier::Colors::TangentLine);
		Canvas2D::DrawLine(points[i * 3 + 0], points[i * 3 + 1]);
		Canvas2D::DrawLine(points[i * 3 + 2], points[i * 3 + 3]);
	}
	for (uint i = 0; i < buttons.size(); i++)
	{
		int rem = i % 3;
		RGBAFloat color = (rem == 1 || rem == 2) ? Bezier::Colors::TangentPoint : Bezier::Colors::Anchor;
		color *= (buttons[i]->IsMouseOver() ? 0.7f : 1.0f);
		buttons[i]->shape->Draw(color);
	}
}

void BezierCurve::OnButtonDrag(Button* button)
{
	int idx = GetButtonIndex(button);
	points[idx] += EventSystem::MousePositionDelta;
	button->shape->Translate(EventSystem::MousePositionDelta);
	if (IsAnchor(idx))
	{
		TranslatePoint(idx + 1, EventSystem::MousePositionDelta);
		TranslatePoint(idx - 1, EventSystem::MousePositionDelta);
	}
	else 
	{
		int oppositeTangentIdx = (IsAnchor(idx + 1)) ? idx + 2 : idx - 2;
		int anchorIdx = (IsAnchor(idx + 1)) ? idx + 1: idx - 1;
		if (InsideBezier(oppositeTangentIdx)) 
		{
			Float2 movedPoint = points[idx];
			Float2 anchor = points[anchorIdx];
			Float2 oppositeTangent = points[oppositeTangentIdx];

			float distance = Float2::Distance(anchor, oppositeTangent);

			Float2 dif = movedPoint - anchor;
			dif.Normalize();
			SetPoint(oppositeTangentIdx, anchor - dif * distance);
		}
	}
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

void BezierCurve::OnMouseClick()
{
	if (ButtonClick() == false)
	{
		AddSegment(EventSystem::MousePosition);
	}
}

bool BezierCurve::InsideBezier(int idx)
{
	return (idx >= 0 && idx < points.size());
}

bool BezierCurve::IsAnchor(int idx)
{
	return idx % 3 == 0;
}

bool BezierCurve::IsTangent(int idx)
{
	return !IsAnchor(idx);
}

void BezierCurve::TranslatePoint(int idx, Float2 delta)
{
	if (InsideBezier(idx))
	{
		points[idx] += delta;
		buttons[idx]->shape->Translate(delta);
	}
}

void BezierCurve::SetPoint(int idx, Float2 pos)
{
	if (InsideBezier(idx))
	{
		points[idx] = pos;
		buttons[idx]->shape->SetPosition(pos);
	}
}

bool BezierCurve::ButtonClick()
{
	for (auto&& btn : buttons)
	{
		if (btn->IsMouseOver())
		{
			return true;
		}
	}
	return false;
}

void BezierCurve::AddPoint(Float2 point, bool anchor)
{
	points.push_back(point);
	Button* btn = new Button(Bezier::Colors::Anchor, new Circle(point, anchor
		? Bezier::AnchorButtonSize
		: Bezier::TangentButtonSize));
	buttons.push_back(btn);
	btn->DragCallback.Register([this](Button* dragBtn) {this->OnButtonDrag(dragBtn); });
}

void BezierCurve::DrawBezierSegment(Float2 a, Float2 b, Float2 c, Float2 d)
{
	Canvas2D::SetColor(color);
	for (float f = 0.0f; f <= 1.0f; f += 0.005f)
	{
		Float2 point = Interpolation::Cubic(a, b, c, d, f);
		Canvas2D::DrawFilledCircle(point, 8, 32);
	}
}
