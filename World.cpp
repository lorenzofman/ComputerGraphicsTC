#include "World.h"
bool World::IsAltPressed = false;
bool World::IsCtrlPressed = false;
bool World::IsShiftPressed = false;

World::Input World::CurrentInput = Input::None;

Shape* World::SelectedShape = nullptr;
std::vector<Shape*> World::Shapes;

World::InterfaceState World::CurrentState = World::InterfaceState::Idle;
Callback<void> World::InputCallback = nullptr;
Int2 World::MousePosition;
Int2 World::MousePositionDelta;
int World::MouseScrollDelta = 0;

std::string World::InputField;

void World::Boot()
{
	Canvas2D(&Screen::Width, &Screen::Height, std::string("Canvas"), &World::OnKeyDown, &World::OnKeyUp, &World::OnMouseUpdate, &World::OnRender);
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

void World::OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
    MouseScrollDelta = (wheel) ? direction : 0;
    MousePositionDelta = Int2(x, y) - MousePosition;
    MousePosition = Int2(x, y);
    if (button == (int)MouseButton::Left && state == (int) MouseButtonState::Down)
    {
        CurrentInput = Input::Select;
    }
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
        case World::Key::Colon: CurrentInput = Input::Colon; break;

        case World::Key::Ctrl_P: CurrentInput = Input::NewPolygon; break;
        case World::Key::Ctrl_R: CurrentInput = Input::NewRectangle; break;
        case World::Key::Ctrl_C: CurrentInput = (IsCtrlPressed) ? Input::NewCircle : Input::None; break;

        case World::Key::Ctrl_O: CurrentInput = Input::Open; break;
        case World::Key::Ctrl_S: CurrentInput = Input::Save; break;

        case World::Key::Num_0: CurrentInput = Input::Num0; break;
        case World::Key::Num_1: CurrentInput = Input::Num1; break;
        case World::Key::Num_2: CurrentInput = Input::Num2; break;
        case World::Key::Num_3: CurrentInput = Input::Num3; break;
        case World::Key::Num_4: CurrentInput = Input::Num4; break;
        case World::Key::Num_5: CurrentInput = Input::Num5; break;
        case World::Key::Num_6: CurrentInput = Input::Num6; break;
        case World::Key::Num_7: CurrentInput = Input::Num7; break;
        case World::Key::Num_8: CurrentInput = Input::Num8; break;
        case World::Key::Num_9: CurrentInput = Input::Num9; break;

        case World::Key::E: CurrentInput = Input::Edit; break;
        case World::Key::B: CurrentInput = Input::SendBackward; break;
        case World::Key::F: CurrentInput = Input::BringForward; break;
        case World::Key::C: CurrentInput = (IsAltPressed) ? Input::ChangeColor : Input::ChangeOutlineColor; break;
        
        case World::Key::G: CurrentInput = Input::Grab; break;
        case World::Key::R: CurrentInput = Input::Rotate; break;
        case World::Key::S: CurrentInput = Input::Scale; break;

        default: break;
	}
}

void World::OnRender()
{
    Canvas2D::ClearScreen(Background);
    Canvas2DExtensions::DrawRoundedRect(Rect2D(128, 128, 384, 384), Selection, 50);
    ProcessState();
    RenderShapes();
    MousePositionDelta = Int2(0, 0);
	MouseScrollDelta = 0;
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
        case World::InterfaceState::InputListening:
            ListenToInput();
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
        case World::Input::ChangeColor:
            break;
        case World::Input::ChangeOutlineColor:
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
        case World::Input::NewCircle:
            InputCallback = &CreateCircle;
            CurrentState = World::InterfaceState::InputListening;
            break;
        case World::Input::NewRectangle:
            InputCallback = &CreateRectangle;
            CurrentState = World::InterfaceState::InputListening;
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
    SetSelectedShape(GetFirstObjectMouseIsInside());
}

Shape* World::GetFirstObjectMouseIsInside()
{
    for (uint i = 0; i < Shapes.size(); i++)
    {
        if (Shapes[i]->IsPointInside(MousePosition))
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
    SelectedShape = selected;
}

void World::ListenToInput()
{
    switch (CurrentInput)
    {
        case World::Input::Num0:
        case World::Input::Num1:
        case World::Input::Num2:
        case World::Input::Num3:
        case World::Input::Num4:
        case World::Input::Num5:
        case World::Input::Num6:
        case World::Input::Num7:
        case World::Input::Num8:
        case World::Input::Num9:
        case World::Input::Colon:
            InputField += (char) CurrentInput;
            break;
        case World::Input::Confirm:
            InputCallback();
            InputCallback = nullptr;
            CurrentState = World::InterfaceState::Idle;
            break;
        default:
            break;
    }
}

void World::UpdateOutlineThickness()
{

}

void World::BringForward()
{
	if (SelectedShape == nullptr)
	{
		return;
	}
	RemoveShape(SelectedShape);
	Shapes.insert(Shapes.begin(), SelectedShape);
}

void World::SendBackward()
{
	RemoveShape(SelectedShape);
	Shapes.push_back(SelectedShape);
}

void World::GrabSelected()
{
    SelectedState();
    if (SelectedShape == nullptr) 
    {
        return;
    }
    SelectedShape->Translate(Float2(MousePositionDelta));
}

void World::RotateSelected()
{
    SelectedState();
    if (SelectedShape == nullptr)
    {
        return;
    }
    Float2 lastMousePosition = MousePosition - MousePositionDelta;

    Float2 currentDifToCenter  = SelectedShape->GetCenter() - MousePosition;
    Float2 previousDifToCenter = SelectedShape->GetCenter() - lastMousePosition;

    float currentAngleToCenter  = atan2f(currentDifToCenter.x, currentDifToCenter.y);
    float previousAngleToCenter = atan2f(previousDifToCenter.x, previousDifToCenter.y);

    float rotationDelta = previousAngleToCenter - currentAngleToCenter;
    SelectedShape->Rotate(rotationDelta);
}

void World::ScaleSelected()
{
    SelectedState();
    if (SelectedShape == nullptr)
    {
        return;
    }
    float currentDistance = Float2::Distance(MousePosition, SelectedShape->GetCenter());
    float previousDistance = Float2::Distance(MousePosition - MousePositionDelta, SelectedShape->GetCenter());

    float scaleDelta = currentDistance / previousDistance;
    SelectedShape->Scale(scaleDelta);
}

void World::Delete()
{
	RemoveShape(SelectedShape);
}

void World::OpenFile()
{

}

void World::SaveFile()
{

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
	/* Todo: Parse String properly*/
	Shapes.push_back(new Circle(128, RGBAFloat(1, 0, 0)));
}

void World::CreateRectangle()
{
	Shapes.push_back(new class Rectangle(Rect2D(128, 128, 384, 384), RGBAFloat(1, 0, 0), RGBAFloat(1, 0, 0), 0));
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


