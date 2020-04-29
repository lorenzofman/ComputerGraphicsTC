#pragma once

#include <vector>
#include <iostream>
#include <functional>

#include "../Interfaces/IRenderable.h"
#include "../Primitives/Float2.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Constants.h"
#include "../Primitives/Types.h"
#include "../Primitives/Circle.h"
#include "../DataStructures/Array.h"
#include "../Helpers/Interpolation.h"
#include "../Helpers/MathExtensions.h"
#include "../Canvas2D/Canvas2D.h"
#include "../Canvas2D/Canvas2DExtensions.h"
#include "../World/Screen.h"
#include "../UI/Button.h"
#include "../Primitives/Rect.h"

class BezierCurve : public IRenderable
{
	public:
	BezierCurve();
	BezierCurve(const Float2& start, const RGBAFloat& color);
	void AddSegment(const Float2& point);
	virtual void Render() override;
	void OnButtonDrag(Button* button);
	void OnMouseClick();
	void StartAnimation();
	void SetDrawConstructionGraph();
	void SetDrawBlendingFunctions();
	void SetDrawControlGraph();
	private:
	
	std::vector<Float2> points = std::vector<Float2>();
	std::vector<Button*> buttons = std::vector<Button*>();
	std::vector<std::function<float(float)>> functions;

	int segmentsCount;

	RGBAFloat color;

	float animationPercent;

	bool drawConstructionGraph;
	bool drawBlendingFunctions;
	bool drawControlGraph;


	bool InsideBezier(const uint& idx);
	bool IsAnchor(const uint& idx);
	bool IsTangent(const uint& idx);
	
	void TranslatePoint(const uint& idx, const Float2& delta);
	void SetPoint(const uint& idx, const Float2& delta);
	
	bool ButtonClick();
	uint GetButtonIndex(Button* button);
	
	void AddPoint(const Float2& point, const bool& anchor);
	
	void DrawBezierSegment(const Float2& a, const Float2& b, const Float2& c, const Float2& d, const float& end = 1.0f);
	void DrawAnimatedCurve(const float&);
	void DrawConstructionGraph(const float&);
	void DrawBlendingFunctions(const float&);
	void AdjustToRect(Float2& point, const int& width, const int& height);
	void DrawConstruction(const Float2& c, const Float2& cd);
	void DrawControlGraph();
	void DrawCurve();
	void DrawEditor();

	void CreateBlendingFunctions();
};

