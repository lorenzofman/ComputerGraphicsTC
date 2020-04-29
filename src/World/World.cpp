#include "World.h"
World::World()
{
	EventSystem::UpdateCallback.Register([this] {this->OnUpdate(); });
	EventSystem::KeyDownCallback.Register([this] (int key) {this->OnKeyDown(key); });
	bezier = new BezierCurve();
}

void World::OnUpdate()
{
	Canvas2D::ClearScreen(Colors::Background);
	bezier->Render();
}

void World::OnKeyDown(int key)
{
	if (key == ' ')
	{
		bezier->StartAnimation();
	}
}
