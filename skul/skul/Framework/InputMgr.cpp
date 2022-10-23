#include "InputMgr.h"
#include <iostream>
#include <algorithm>
#include "Framework.h"

map<Axis, AxisInfo> InputMgr::axisInfoMap;

list<Keyboard::Key> InputMgr::downList;
list<Keyboard::Key> InputMgr::ingList;
list<Keyboard::Key> InputMgr::upList;

list<Mouse::Button> InputMgr::downMouse;
list<Mouse::Button> InputMgr::ingMouse;
list<Mouse::Button> InputMgr::upMouse;

int InputMgr::mouseWheelMoved;

Vector2f InputMgr::mousePos;

void InputMgr::Init()
{
	// Horizontal
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positives.push_back(Keyboard::Key::D);
	infoH.positives.push_back(Keyboard::Key::Right);

	infoH.negatives.push_back(Keyboard::Key::A);
	infoH.negatives.push_back(Keyboard::Key::Left);

	infoH.sensi = 5.f;
	infoH.value = 0.f;

	axisInfoMap.insert({ infoH.axis, infoH });

	// Vertical
	AxisInfo infoV;
	infoV.axis = Axis::Vertical;

	infoV.positives.push_back(Keyboard::Key::S);
	infoV.positives.push_back(Keyboard::Key::Down);

	infoV.negatives.push_back(Keyboard::Key::W);
	infoV.negatives.push_back(Keyboard::Key::Up);


	infoV.sensi = 5.f;
	infoV.value = 0.f;

	axisInfoMap.insert({ infoV.axis, infoV });
}

void InputMgr::Update(float dt)
{
	downList.clear();
	upList.clear();
	downMouse.clear();
	upMouse.clear();

	mouseWheelMoved = 0.f;

	for (auto& it : axisInfoMap)
	{
		AxisInfo& axis = it.second;
		float raw = GetAxisRaw(axis.axis);
		if (raw == 0.f)
		{
			if (axis.value != 0.f)
			{
				raw = axis.value > 0.f ? -1.f : 1.f;
			}
		}
		axis.value += raw * axis.sensi * dt;
		axis.value = min(axis.value, 1.f);
		axis.value = max(axis.value, -1.f);

		if (abs(axis.value) < 0.001f)
			axis.value = 0.f;
	}

	mousePos = (Vector2f)Mouse::getPosition(FRAMEWORK->GetWindow());
}

void InputMgr::ProcessInput(Event& ev)
{
	switch (ev.type)
	{
	case Event::EventType::MouseButtonPressed:
		if (find(ingMouse.begin(), ingMouse.end(), ev.key.code) == ingMouse.end())
		{
			downMouse.push_back(ev.mouseButton.button);
			ingMouse.push_back(ev.mouseButton.button);
		}
		break;
	case Event::EventType::MouseButtonReleased:
		{
			ingMouse.remove(ev.mouseButton.button);
			upMouse.push_back(ev.mouseButton.button);
			break;
		}
	case Event::EventType::MouseWheelScrolled:
		{
			mouseWheelMoved = ev.mouseWheelScroll.delta;
			break;
		}
	case Event::EventType::KeyPressed:
		if (find(ingList.begin(), ingList.end(), ev.key.code) == ingList.end())
		{
			downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);
		}
		break;
	case Event::EventType::KeyReleased:
		{
			ingList.remove(ev.key.code);
			upList.push_back(ev.key.code);
			break;
		}
	}
}

bool InputMgr::GetKeyDown(Keyboard::Key key)
{
	return find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(Keyboard::Key key)
{
	return find(ingList.begin(), ingList.end(), key) != ingList.end();
}

bool InputMgr::GetKeyUp(Keyboard::Key key)
{
	return find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetMouseButtonDown(Mouse::Button key)
{
	return find(downMouse.begin(), downMouse.end(), key) != downMouse.end();;
}

bool InputMgr::GetMouseButton(Mouse::Button key)
{
	return find(ingMouse.begin(), ingMouse.end(), key) != ingMouse.end();
}

bool InputMgr::GetMouseButtonUp(Mouse::Button key)
{
	return find(upMouse.begin(), upMouse.end(), key) != upMouse.end();;
}

float InputMgr::GetMouseWheelMoved()
{
	return mouseWheelMoved;
}

const Vector2f& InputMgr::GetMousePos()
{
	return mousePos;
}

float InputMgr::GetAxis(Axis axis)
{
	return axisInfoMap[axis].value;
}

float InputMgr::GetAxisRaw(Axis axis)
{
	const AxisInfo& info = axisInfoMap[axis];

	auto it = ingList.rbegin();
	while (it != ingList.rend())
	{
		Keyboard::Key key = *it;
		if (find(info.negatives.begin(), info.negatives.end(), key) !=
			info.negatives.end())
		{
			return -1.f;
		}
		if (find(info.positives.begin(), info.positives.end(), key) !=
			info.positives.end())
		{
			return 1.f;
		}
		++it;
	}
	return 0.f;

}
