#include "World.h"
World::World()
{
	EventSystem::UpdateCallback.Register([this] {this->Update(); });
	bezier = new BezierCurve();
}

void World::Update()
{
	Canvas2D::ClearScreen(Colors::Background);
	bezier->Render();
}
