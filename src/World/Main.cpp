#include "EventSystem.h"
#include "World.h"
#include "Screen.h"
#include "../Canvas2D/Canvas2D.h"
int main()
{
	new World();
	EventSystem::Configure();
	Canvas2D(&Screen::Height, &Screen::Width, std::string("Canvas"), &EventSystem::OnKeyDown, &EventSystem::OnKeyUp, &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate);
}
