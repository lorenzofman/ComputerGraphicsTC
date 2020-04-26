#pragma once

#include "Float2.h"
#include "RGBAFloat.h"
class Shape
{
	public:
	
	virtual bool IsPointInside(Float2) = 0;
	virtual void Draw(RGBAFloat) = 0;
	virtual void Translate(Float2) = 0;
};