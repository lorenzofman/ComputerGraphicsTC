#pragma once

#include <vector>
#include <unordered_map>

class IAnyKeyDownListener;
class IAnyKeyUpListener;

class IKeyDownListener;
class IKeyUpListener;

class IMouseListener;

class ILeftMouseButtonDownListener;
class ILeftMouseButtonUpListener;

class IRightMouseButtonDownListener;
class IRightMouseButtonUpListener;

class IMiddleMouseButtonDownListener;
class IMiddleMouseButtonUpListener;

class IMouseWheelUpdateListener;

#include "Scene.h"

#include "IAnyKeyDownListener.h"
#include "IAnyKeyUpListener.h"
#include "IMouseListener.h"
#include "IKeyDownListener.h"
#include "IKeyUpListener.h"

#include "ILeftMouseButtonDownListener.h"
#include "ILeftMouseButtonUpListener.h"

#include "IRightMouseButtonDownListener.h"
#include "IRightMouseButtonUpListener.h"

#include "IMiddleMouseButtonDownListener.h"
#include "IMiddleMouseButtonUpListener.h"

#include "IMouseWheelUpdateListener.h"

#include "Float2.h"
enum class MouseWheelDirection {Down = -1, Up = 1};
class InputHandler : public IAnyKeyDownListener, public IAnyKeyUpListener, public IMouseListener
{
	public:

	InputHandler(Scene* scene);

	virtual void OnKeyDown(int) override;

	virtual void OnKeyUp(int) override;

	virtual void OnMouseUpdate(int, int, int, int, int, int) override;

	Float2 GetMousePosition();

	void RegisterOnKeyDown(int, IKeyDownListener*);
	void RegisterOnKeyUp(int, IKeyUpListener*);

	void RegisterLeftMouseButtonDownListener(ILeftMouseButtonDownListener*);
	void RegisterLeftMouseButtonUpListener(ILeftMouseButtonUpListener*);
	
	void RegisterRightMouseButtonDownListener(IRightMouseButtonDownListener*);
	void RegisterRightMouseButtonUpListener(IRightMouseButtonUpListener*);

	void RegisterMiddleMouseButtonDownListener(IMiddleMouseButtonDownListener*);
	void RegisterMiddleMouseButtonUpListener(IMiddleMouseButtonUpListener*);
	
	void RegisterMouseWheelUpdateListener(IMouseWheelUpdateListener*);

	void DeregisterLeftMouseButtonDownListener(ILeftMouseButtonDownListener*);
	void DeregisterLeftMouseButtonUpListener(ILeftMouseButtonUpListener*);

	void DeregisterRightMouseButtonDownListener(IRightMouseButtonDownListener*);
	void DeregisterRightMouseButtonUpListener(IRightMouseButtonUpListener*);

	void DeregisterMiddleMouseButtonDownListener(IMiddleMouseButtonDownListener*);
	void DeregisterMiddleMouseButtonUpListener(IMiddleMouseButtonUpListener*);

	void DeregisterMouseWheelUpdateListener(IMouseWheelUpdateListener*);

	private:

	void MouseButtonsCallbacks(int button, int state);

	void MouseWheelCallback(int direction);

	void OnLeftMouseButtonDown();
	void OnLeftMouseButtonUp();

	void OnMiddleMouseButtonDown();
	void OnMiddleMouseButtonUp();

	void OnRightMouseButtonDown();
	void OnRightMouseButtonUp();

	void OnMouseWheelUpdate(MouseWheelDirection dir);

	void (InputHandler::* mouseCallbacks[3][2])() =
	{
		{ &InputHandler::OnLeftMouseButtonDown,		&InputHandler::OnLeftMouseButtonUp},
		{ &InputHandler::OnMiddleMouseButtonDown,	&InputHandler::OnMiddleMouseButtonUp},
		{ &InputHandler::OnRightMouseButtonDown,	&InputHandler::OnRightMouseButtonUp} ,
	};


	std::unordered_map<int, std::vector<IKeyDownListener*>> keyDownListeners;
	std::unordered_map<int, std::vector<IKeyUpListener*>> keyUpListeners;

	std::vector<ILeftMouseButtonDownListener*> leftMouseButtonDownListeners;
	std::vector<ILeftMouseButtonUpListener*> leftMouseButtonUpListeners;

	std::vector<IRightMouseButtonDownListener*> rightMouseButtonDownListeners;
	std::vector<IRightMouseButtonUpListener*> rightMouseButtonUpListeners;

	std::vector<IMiddleMouseButtonDownListener*> middleMouseButtonDownListeners;
	std::vector<IMiddleMouseButtonUpListener*> middleMouseButtonUpListeners;

	std::vector<IMouseWheelUpdateListener*> mouseWheelUpdateListeners;

	Float2 mousePosition;
};