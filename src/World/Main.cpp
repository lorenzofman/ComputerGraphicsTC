#include "EventSystem.h"
#include "World.h"
#include "../UI/ShapeTransformer.h"
#include "../Color/ColorPalette.h"
int main()
{
	int hs = Colors::Palette::ButtonHalfSize;
	ShapeTransformer transformer = ShapeTransformer();
	ColorPalette main = ColorPalette(Int2(hs * 8, hs));
	ColorPalette outline = ColorPalette(Int2(hs * 20, hs));
	new World(transformer, main, outline);
	Canvas2D(&Screen::Width, &Screen::Height, std::string("Canvas"), &EventSystem::OnKeyDown, &EventSystem::OnKeyUp, &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate);
}
