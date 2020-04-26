#include "EventSystem.h"
#include "World.h"
#include "Screen.h"
#include "../Canvas2D/Canvas2D.h"
int main()
{
	new World();
	Canvas2D(&Screen::Width, &Screen::Height, std::string("Canvas"), &EventSystem::OnKeyDown, &EventSystem::OnKeyUp, &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate);
}
