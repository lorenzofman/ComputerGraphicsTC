#include "World.h"

World::World(ShapeTransformer& transformer, ColorPalette& mainColorPalette, ColorPalette& outlineColorPalette) : 
    transformerRef(transformer),
    mainColorPaletteRef(mainColorPalette),
    outlineColorPaletteRef(outlineColorPalette)
{
    EventSystem::UpdateCallback.Register([this] {this->OnRender(); });
    EventSystem::KeyDownCallback.Register([this](int key) {this->OnKeyDown(key); });
    EventSystem::KeyUpCallback.Register([this](int key) {this->OnKeyUp(key); });
    EventSystem::LeftMouseButtonDownCallback.Register([this] {this->OnLeftMouseButtonDown(); });
    EventSystem::MouseWheelCallback.Register([this] {this->OnMouseWheelUpdate(); });
    mainColorPaletteRef.colorUpdateCallback.Register([this] (RGBAFloat color) {this->UpdateMainColor(color);});
    outlineColorPaletteRef.colorUpdateCallback.Register([this](RGBAFloat color) {this->UpdateOutlineColor(color);});
    selectedShape = nullptr;
    
    IsAltPressed = false;
    IsCtrlPressed = false;
    IsShiftPressed = false;

    CurrentInput = Input::None;
    CurrentState = InterfaceState::Idle;
}

void World::OnKeyDown(int key)
{
	ProcessModifiers(key, true);
	ProcessInput(key);
}

void World::OnKeyUp(int key)
{
	ProcessModifiers(key, false);
}

void World::OnLeftMouseButtonDown()
{
    CurrentInput = Input::Select;
}

void World::OnMouseWheelUpdate()
{
	CurrentInput = Input::MouseWheelUpdate;
}

void World::ProcessModifiers(int key, bool pressed)
{
	switch (key)
	{
		case 212: IsShiftPressed = pressed; break;
		case 214: IsCtrlPressed = pressed; break;
		case 216: IsAltPressed = pressed; break;
		default: break;
	}
}

void CaseInvariant(int& key)
{
	if (key >= 'a' && key <= 'z')
	{
		key -= ('a' - 'A');
	}
}

void World::ProcessInput(int input)
{
	CaseInvariant(input);
	World::Key key = (World::Key) input;
	switch (key)
	{
        case World::Key::Enter: CurrentInput = Input::Confirm; break;
        case World::Key::Delete: CurrentInput = Input::Delete; break;

        case World::Key::Ctrl_C: CurrentInput = Input::CreateCircle; break;
		case World::Key::Ctrl_E: CurrentInput = Input::CreateEquilatereumTriangle; break;
		case World::Key::Ctrl_H: CurrentInput = Input::CreateHexagon; break;
		case World::Key::Ctrl_I: CurrentInput = Input::CreateIsoscelesTriangle; break;
		case World::Key::Ctrl_K: CurrentInput = Input::CreateOctagon; break;
		case World::Key::Ctrl_P: CurrentInput = Input::CreatePentagon; break;
        case World::Key::Ctrl_R: CurrentInput = Input::CreateRectangle; break;
		case World::Key::Ctrl_T: CurrentInput = Input::CreateRectangleTriangle; break;

        case World::Key::Ctrl_O: CurrentInput = Input::Open; break;
        case World::Key::Ctrl_S: CurrentInput = Input::Save; break;

        case World::Key::B: CurrentInput = Input::SendBackward; break;
        case World::Key::F: CurrentInput = Input::BringForward; break;

        case World::Key::G: CurrentInput = Input::Grab; break;
        case World::Key::R: CurrentInput = Input::Rotate; break;
        case World::Key::S: CurrentInput = Input::Scale; break;

        default: break;
	}
}

void World::OnRender()
{
    Canvas2D::ClearScreen(Colors::Background);
    ProcessState();
    RenderShapes();

	transformerRef.Render();

	Canvas2D::SetColor(Colors::White);
	Canvas2D::DrawText(0, Colors::Palette::ButtonHalfSize - 5, "Fill Color:");
    mainColorPaletteRef.Render();

	Canvas2D::SetColor(Colors::White);
	Canvas2D::DrawText(160, Colors::Palette::ButtonHalfSize - 5, "Outline Color:");
    outlineColorPaletteRef.Render();

}

void World::ProcessState()
{
    switch (CurrentState)
    {
        case World::InterfaceState::Grabbing:
            GrabSelected();
            break;
        case World::InterfaceState::Rotating:
            RotateSelected();
            break;
        case World::InterfaceState::Scaling:
            ScaleSelected();
            break;
        case World::InterfaceState::ShapeSelected:
            SelectedState();
            break;
        case World::InterfaceState::Idle:
            IdleState();
            break;
        default:
            break;
    }
    CurrentInput = World::Input::None;
}

void World::SelectedState()
{
    switch (CurrentInput)
    {
        case World::Input::Grab:
            CurrentState = World::InterfaceState::Grabbing;
            break;
        case World::Input::Rotate:
            CurrentState = World::InterfaceState::Rotating;
            break;
        case World::Input::Scale:
            CurrentState = World::InterfaceState::Scaling;
            break;
        case World::Input::MouseWheelUpdate:
            UpdateOutlineThickness();
            break;
        case World::Input::BringForward:
            BringForward();
            break;
        case World::Input::SendBackward:
            SendBackward();
            break;
        case World::Input::Delete:
            Delete();
            break;
        default:
            break;
    }
    IdleState();
}

void World::IdleState()
{
    switch (CurrentInput)
    {
        case World::Input::Select:
            SelectObject();
            break;
        case World::Input::CreateCircle:
            CreateCircle();
            break;
        case World::Input::CreateEquilatereumTriangle:
            CreateEquilatereumTriangle();
            break;
        case World::Input::CreateHexagon:
            CreateHexagon();
            break;
        case World::Input::CreateIsoscelesTriangle:
            CreateIsoscelesTriangle();
            break;
		case World::Input::CreateOctagon:
			CreateOctagon();
			break;
		case World::Input::CreatePentagon:
			CreatePentagon();
            break;
        case World::Input::CreateRectangleTriangle:
			CreateRectangleTriangle();
            break;
        case World::Input::CreateRectangle:
            CreateRectangle();
            break;
        case World::Input::Open:
            OpenFile();
            break;
        case World::Input::Save:
            SaveFile();
            break;
    }
}

void World::SelectObject()
{
    if (transformerRef.IsMouseOver() == false &&
		mainColorPaletteRef.IsMouseOver() == false &&
		outlineColorPaletteRef.IsMouseOver() == false)
    {
        SetSelectedShape(GetFirstObjectMouseIsInside());
    }
}

Shape* World::GetFirstObjectMouseIsInside()
{
    for (uint i = 0; i < Shapes.size(); i++)
    {
        if (Shapes[i]->IsPointInside(EventSystem::MousePosition))
        {
            CurrentState = InterfaceState::ShapeSelected;
            return Shapes[i];
        }
    }
    if (CurrentState == InterfaceState::ShapeSelected)
    {
        CurrentState = InterfaceState::Idle;
    }
    return nullptr;
}

void World::SetSelectedShape(Shape* selected)
{
    selectedShape = selected;
	transformerRef.SetShape(selected);
}

void World::UpdateOutlineThickness()
{
	if (selectedShape == nullptr)
	{
		return;
	}
	float currentThickness = selectedShape->GetOutlineThickness();
	float change = EventSystem::MouseScrollDelta * OutlineScrollSpeed;
	selectedShape->SetOutlineThickness(currentThickness + change);
}

void World::BringForward()
{
	if (selectedShape == nullptr)
	{
		return;
	}
	RemoveShape(selectedShape);
	Shapes.insert(Shapes.begin(), selectedShape);
}

void World::SendBackward()
{
	RemoveShape(selectedShape);
	Shapes.push_back(selectedShape);
}

void World::GrabSelected()
{
    SelectedState();
    if (selectedShape == nullptr)
    {
        return;
    }
    selectedShape->Translate(Float2(EventSystem::MousePositionDelta));
}

void World::RotateSelected()
{
    SelectedState();
    if (selectedShape == nullptr)
    {
        return;
    }
    Float2 lastMousePosition = EventSystem::MousePosition - EventSystem::MousePositionDelta;

    Float2 currentDifToCenter  = selectedShape->GetCenter() - EventSystem::MousePosition;
    Float2 previousDifToCenter = selectedShape->GetCenter() - lastMousePosition;

    float currentAngleToCenter  = atan2f(currentDifToCenter.x, currentDifToCenter.y);
    float previousAngleToCenter = atan2f(previousDifToCenter.x, previousDifToCenter.y);

    float rotationDelta = previousAngleToCenter - currentAngleToCenter;
    selectedShape->Rotate(rotationDelta);
}

void World::ScaleSelected()
{
    SelectedState();
    if (selectedShape == nullptr)
    {
        return;
    }
    float currentDistance = Float2::Distance(EventSystem::MousePosition, selectedShape->GetCenter());
    float previousDistance = Float2::Distance(EventSystem::MousePosition - EventSystem::MousePositionDelta, selectedShape->GetCenter());
    float scaleDelta = currentDistance / previousDistance;

    if (ResultingRectIsBigEnough(scaleDelta) == false)
    {
        return;
    }

    selectedShape->Scale(scaleDelta);
}

bool World::ResultingRectIsBigEnough(float scaleDelta)
{
    Rect rect = selectedShape->GetRect();
    rect.Scale(scaleDelta);
    Float2 dif = rect.TopRight - rect.BottomLeft;
    return (dif.x >= MinShapeSize || dif.y >= MinShapeSize);
}

void World::Delete()
{
	RemoveShape(selectedShape);
	delete selectedShape;
    transformerRef.SetShape(nullptr);
}

void World::OpenFile()
{
    for (int i = Shapes.size() - 1; i >= 0; i--)
    {
        delete Shapes[i];
    }
    Shapes.clear();
    Array<Shape*> arr = ShapeSerializer::Deserialize("Shapes.gr");
    Shapes.reserve(arr.size);
    for (int i = 0; i < arr.size; i++)
    {
        Shapes.push_back(arr.ptr[i]);
    }
    delete[] arr.ptr;
}

void World::SaveFile()
{
    ShapeSerializer::Serialize("Shapes.gr", Array<Shape*>(&Shapes[0], Shapes.size()));
}

void World::UpdateMainColor(RGBAFloat color)
{
    if (selectedShape == nullptr)
    {
        return;
    }
    selectedShape->SetMainColor(color);
}

void World::UpdateOutlineColor(RGBAFloat color)
{
	if (selectedShape == nullptr)
	{
		return;
	}
    selectedShape->SetOutlineColor(color);
}

void World::RenderShapes()
{
    for (int i = Shapes.size() - 1; i >= 0; i--)
    {
        Shapes[i]->Render();
    }
}

void World::CreateCircle()
{
	Shapes.push_back(new Circle(128, mainColorPaletteRef.GetCurrentColor()));
}

void World::CreateRectangle()
{
	Rect rect = Rect(Float2(Screen::Center()), 128);
	Shapes.push_back(new class Rectangle(rect, mainColorPaletteRef.GetCurrentColor()));
}

void World::CreateRectangleTriangle()
{
    Float2* vertices = new Float2[3];
	vertices[0] = Float2(-80, 100);
	vertices[1] = Float2(80, -100);
	vertices[2] = Float2(-80, -100);
	CreateTriangle(vertices);
}

void World::CreateIsoscelesTriangle()
{
	Float2* vertices = new Float2[3];
	vertices[0] = Float2(-75, -100);
	vertices[1] = Float2(0, 100);
	vertices[2] = Float2(75, -100);
	CreateTriangle(vertices);
}

void World::CreateEquilatereumTriangle()
{
	Float2* vertices = new Float2[3];
	vertices[0] = Float2(-75, -50);
	vertices[1] = Float2(0, 50);
	vertices[2] = Float2(75, -50);
	CreateTriangle(vertices);
}

void World::CreateTriangle(Float2* vertices)
{
	Array<Float2> arr = Array<Float2>(vertices, 3);
	CreatePolygon(arr);
}

void World::CreatePentagon()
{
    CreateRegularPolygon(5);
}

void World::CreateHexagon()
{
    CreateRegularPolygon(6);
}

void World::CreateOctagon()
{
    CreateRegularPolygon(8);
}

void World::CreateRegularPolygon(int vertices)
{
    Float2* arr = new Float2[vertices];
    float part = (2 * PI) / vertices;
    for (int i = 1; i <= vertices; i++)
    {
        float rad = part * i;
        arr[vertices - i] = Float2(cos(rad), sin(rad)) * 80;
    }
    CreatePolygon(Array<Float2>(arr, vertices));
}

void World::CreatePolygon(const Array<Float2>& arr)
{
	class Polygon* rectangleTriangle = new class Polygon(arr, mainColorPaletteRef.GetCurrentColor());
	rectangleTriangle->Translate(Screen::Center());
	Shapes.push_back(rectangleTriangle);
}

void World::RemoveShape(Shape* shape)
{
	std::vector<Shape*>::iterator it = std::find(Shapes.begin(), Shapes.end(), shape);
	Shapes.erase(it);
}

/* Todo: Print message to screen*/
void World::Message(const char* str)
{
    std::cout << str << std::endl;
}
