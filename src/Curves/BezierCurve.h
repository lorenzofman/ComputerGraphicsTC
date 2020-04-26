#pragma once

#include <vector>

#include "../Interfaces/IRenderable.h"
#include "../Primitives/Float2.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Constants.h"
#include "../Primitives/Types.h"
#include "../Primitives/Circle.h"
#include "../DataStructures/Array.h"
#include "../Helpers/Interpolation.h"
#include "../Canvas2D/Canvas2D.h"
#include "../World/Screen.h"
#include "../UI/Button.h"

class BezierCurve : public IRenderable
{
	public:
	BezierCurve();
	BezierCurve(Float2 start, RGBAFloat color);
	void AddSegment(Float2 point);
	virtual void Render() override;
	void OnButtonDrag(Button* button);
	void OnMouseClick();
	private:
	
	std::vector<Float2> points = std::vector<Float2>();
	std::vector<Button*> buttons = std::vector<Button*>();
	int segmentsCount;
	RGBAFloat color;

	bool InsideBezier(int idx);
	bool IsAnchor(int idx);
	bool IsTangent(int idx);
	void TranslatePoint(int idx, Float2 delta);
	void SetPoint(int idx, Float2 delta);
	bool ButtonClick();
	int GetButtonIndex(Button* button);
	void AddPoint(Float2 point, bool anchor);
	void DrawBezierSegment(Float2 a, Float2 b, Float2 c, Float2 d);

};

