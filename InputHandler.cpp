#include "InputHandler.h"
#include "IAnyKeyDownListener.h"
#include "IAnyKeyUpListener.h"
#include "IMouseListener.h"
InputHandler::InputHandler(Scene* sc) : IAnyKeyDownListener(sc), IAnyKeyUpListener(sc), IMouseListener(sc)
{

}

void InputHandler::OnKeyDown(int)
{
}

void InputHandler::OnKeyUp(int)
{
}

void InputHandler::OnMouseUpdate(int, int, int, int, int, int)
{
}
