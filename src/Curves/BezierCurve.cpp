#include "BezierCurve.h"

BezierCurve::BezierCurve() : BezierCurve(Screen::Center(), Bezier::Colors::Curve) { }

BezierCurve::BezierCurve(const Float2& center, const RGBAFloat& color)
{
	AddPoint(center + Float2::Left * 100, true);
	AddPoint(center + (Float2::Left + Float2::Up) * 50, false);
	AddPoint(center + (Float2::Right + Float2::Down) * 50, false);
	AddPoint(center + Float2::Right * 100, true);
	segmentsCount = 1;
	this->color = color;
	EventSystem::LeftMouseButtonDownCallback.Register([this] {this->OnMouseClick(); });
	animationPercent = 1;
	drawConstructionGraph = true;
	drawBlendingFunctions = true;
	drawControlGraph = true;
	CreateBlendingFunctions();
}

void BezierCurve::AddSegment(const Float2& anchor)
{
	AddPoint(points[points.size() - 1] * 2 - points[points.size() - 2], false);
	AddPoint((points[points.size() - 1] + anchor) * 0.5f, false);
	AddPoint(anchor, true);
	segmentsCount++;
	animationPercent *= (float) (segmentsCount - 1) / segmentsCount;
}

void BezierCurve::Render()
{
	if (animationPercent < 1.0f) 
	{
		DrawAnimatedCurve(animationPercent);
		animationPercent += 1.0f / (TargetFramesPerSeconds * Bezier::AnimationDurationPerSegment * segmentsCount);
	}
	else 
	{
		DrawCurve();
	}
}

void BezierCurve::DrawCurve()
{
	for (int i = 0; i < segmentsCount; i++)
	{
		DrawBezierSegment(
			points[i * 3 + 0],
			points[i * 3 + 1],
			points[i * 3 + 2],
			points[i * 3 + 3]);
	}
	DrawEditor();
}

void BezierCurve::DrawAnimatedCurve(const float& percent)
{
	float total = percent * segmentsCount;
	for (int i = 0; i < segmentsCount; i++)
	{
		float t;
		if (total > 1.0f)
		{
			total -= 1.0f;
			t = 1.0f;
		}
		else
		{
			t = total;
			total = 0.0f;
		}
		DrawBezierSegment(
			points[i * 3 + 0],
			points[i * 3 + 1],
			points[i * 3 + 2],
			points[i * 3 + 3], t);
	}

	DrawEditor();

	if (drawConstructionGraph)
	{
		DrawConstructionGraph(animationPercent);
	}

	if (drawBlendingFunctions)
	{
		DrawBlendingFunctions(animationPercent);
	}

	

}

void BezierCurve::DrawConstructionGraph(const float& percent)
{
	int currentSegment = (int) (percent * segmentsCount);
	float total = percent * segmentsCount;
	float t = total - currentSegment;

	Float2 a = points[currentSegment * 3 + 0];
	Float2 b = points[currentSegment * 3 + 1];
	Float2 c = points[currentSegment * 3 + 2];
	Float2 d = points[currentSegment * 3 + 3];
	
	Canvas2D::SetColor(Bezier::Colors::Construction::Linear);
	Float2 ab = Interpolation::Linear(a, b, t); 
	Float2 bc = Interpolation::Linear(b, c, t); 
	Float2 cd = Interpolation::Linear(c, d, t);
	DrawConstruction(a, ab);
	DrawConstruction(b, bc);
	DrawConstruction(c, cd);

	Canvas2D::SetColor(Bezier::Colors::Construction::Quadratic);
	Float2 abc = Interpolation::Linear(ab, bc, t); 
	Float2 bcd = Interpolation::Linear(bc, cd, t); 
	DrawConstruction(ab, abc);
	DrawConstruction(bc, bcd);

	Canvas2D::SetColor(Bezier::Colors::Construction::Cubic);
	Float2 abcd = Interpolation::Linear(abc, bcd, t); 
	DrawConstruction(abc, abcd);
}

void BezierCurve::DrawBlendingFunctions(const float& percent)
{
	int currentSegment = (int)(percent * segmentsCount);
	float total = percent * segmentsCount;
	float t = total - currentSegment;

	const int width = Screen::Width/4, height = Screen::Height / 4;
	const float step = (float)1 / width;
	Rect drawingRect = Rect(Screen::Width - width, 0, Screen::Width,  height);

	int idx = 0;
	for (auto&& f : functions)
	{
		Canvas2D::SetColor(Bezier::Colors::BlendingFunctionColors[idx++]);
		for (float x = 0.0f; x < 1.0f; x += step)
		{
			Float2 point = Float2(x, f(x));
			AdjustToRect(point, width, height);
			Canvas2D::DrawPoint(point);
		}
		Float2 point = Float2(t, f(t));
		AdjustToRect(point, width, height);
		Canvas2D::DrawFilledCircle(point, 8, 8);
	}
}

void BezierCurve::AdjustToRect(Float2& point, const int& width, const int& height)
{
	point.x *= width;
	point.x += Screen::Width - width;
	point.y *= height;
}

void BezierCurve::DrawConstruction(const Float2& c, const Float2& cd)
{
	Canvas2D::DrawLine(c, cd);
	Canvas2D::DrawFilledCircle(cd, 4, 8);
}

void BezierCurve::DrawControlGraph()
{
	Canvas2D::SetColor(Bezier::Colors::DashedLine);
	for (int i = 0; i < segmentsCount; i++)
	{
		Canvas2DExtensions::DrawDashedLine(points[i * 3 + 0], points[i * 3 + 1]);
		Canvas2DExtensions::DrawDashedLine(points[i * 3 + 1], points[i * 3 + 2]);
		Canvas2DExtensions::DrawDashedLine(points[i * 3 + 2], points[i * 3 + 3]);
	}
}


void BezierCurve::DrawEditor()
{
	for (int i = 0; i < segmentsCount; i++)
	{
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
	if (drawControlGraph) 
	{
		DrawControlGraph();
	}
}

void BezierCurve::CreateBlendingFunctions()
{
	int controlPoints = 4;
	int n = controlPoints - 1;
	for (int i = 0; i < controlPoints; i++)
	{
		functions.push_back([n, i](float t)
			{
				return MathExtensions::Binomial(n, i) * powf(t, i) * powf(1 - t, n - i);
			});
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

uint BezierCurve::GetButtonIndex(Button* button)
{
	for (uint i = 0; i < buttons.size(); i++)
	{
		if (buttons[i] == button)
		{
			return i;
		}
	}
	throw "Invalid button";
}

void BezierCurve::OnMouseClick()
{
	if (ButtonClick() == false)
	{
		AddSegment(EventSystem::MousePosition);
	}
}

bool BezierCurve::InsideBezier(const uint& idx)
{
	return (idx >= 0 && idx < points.size());
}

bool BezierCurve::IsAnchor(const uint& idx)
{
	return idx % 3 == 0;
}

bool BezierCurve::IsTangent(const uint& idx)
{
	return !IsAnchor(idx);
}

void BezierCurve::TranslatePoint(const uint& idx, const Float2& delta)
{
	if (InsideBezier(idx))
	{
		points[idx] += delta;
		buttons[idx]->shape->Translate(delta);
	}
}

void BezierCurve::SetPoint(const uint& idx, const Float2& pos)
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

void BezierCurve::AddPoint(const Float2& point, const bool& anchor)
{
	points.push_back(point);
	Button* btn = new Button(Bezier::Colors::Anchor, new Circle(point, anchor
		? Bezier::AnchorButtonSize
		: Bezier::TangentButtonSize));
	buttons.push_back(btn);
	btn->DragCallback.Register([this](Button* dragBtn) {this->OnButtonDrag(dragBtn); });
}

void BezierCurve::DrawBezierSegment(const Float2& a, const Float2& b, const Float2& c, const Float2& d, const float& end)
{
	Canvas2D::SetColor(color);
	for (float f = 0.0f; f <= end; f += 0.005f)
	{
		Float2 point = Interpolation::Cubic(a, b, c, d, f);
		Canvas2D::DrawFilledCircle(point, 8, 32);
	}
}

void BezierCurve::StartAnimation()
{
	animationPercent = 0.0f;
}

void BezierCurve::SetDrawConstructionGraph()
{
	drawConstructionGraph = !drawConstructionGraph;
}

void BezierCurve::SetDrawBlendingFunctions()
{
	drawBlendingFunctions != drawBlendingFunctions;
}

void BezierCurve::SetDrawControlGraph()
{
	drawControlGraph = !drawControlGraph;
}
