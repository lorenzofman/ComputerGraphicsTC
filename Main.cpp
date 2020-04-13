#include "World.h"
#include "EventSystem.h"
#include <functional>

void Test(int a)
{

}
int main()
{
	World::BigBang();
	Canvas2D(&Screen::Width, &Screen::Height, std::string("Canvas"), &EventSystem::OnKeyDown, &EventSystem::OnKeyUp, &EventSystem::OnMouseUpdate, &EventSystem::OnUpdate);
}
