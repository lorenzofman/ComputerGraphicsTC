#include "EventSystem.h"
#include "World.h"
#include <Windows.h>
int main()
{
	World::BigBang();
	
	Canvas2D(&Screen::Width, &Screen::Height, std::string("Canvas"), &EventSystem::OnKeyDown, &EventSystem::OnKeyUp, &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate);
}
