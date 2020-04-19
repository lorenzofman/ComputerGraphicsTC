#pragma once
#pragma pack (push, 1)
struct RGBAFloat
{
	float r;
	float g;
	float b;
	float a;
	RGBAFloat();
	RGBAFloat(float r, float g, float b, float a = 1);
	RGBAFloat operator * (float const& constant) const;
	void operator *= (float const& constant);
	static RGBAFloat Blank;
};
#pragma pack (pop)