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
	DisplayFramesPerSeconds();
}

void World::DisplayFramesPerSeconds()
{
	int fps = (int) (1.0 / EventSystem::LastFrameDuration);
	char* str = new char[11];
	sprintf(str, "%i", fps);
	Canvas2D::DrawText(Float2::Zero, str);
}

void World::OnKeyDown(int key)
{
	switch (key)
	{
	case ' ':
	{
		bezier->StartAnimation();
		break;
	}
	case 'c':
	{
		bezier->SetDrawConstructionGraph();
		break;
	}
	case 'f':
	{
		bezier->SetDrawBlendingFunctions();
		break;
	}
	case 'g':
	{
		bezier->SetDrawControlGraph();
		break;
	}
	default: break;
	}
}
