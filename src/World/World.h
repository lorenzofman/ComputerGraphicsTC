#pragma once
#include "EventSystem.h"
#include "Screen.h"
#include "../Curves/BezierCurve.h"
#include "../Canvas2D/Canvas2D.h"
#include "../Primitives/Constants.h"
class World 
{
	public:

	World();

	private:

	BezierCurve* bezier;
	void OnUpdate();
	void OnKeyDown(int);
};