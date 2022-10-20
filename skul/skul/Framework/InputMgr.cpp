#include "InputMgr.h"
#include <iostream>
#include <algorithm>

map<Axis, AxisInfo> InputMgr::axisInfoMap;

vector<bool> InputMgr::downList(Keyboard::Key::KeyCount);
vector<bool> InputMgr::ingList(Keyboard::Key::KeyCount);
vector<bool> InputMgr::upList(Keyboard::Key::KeyCount);
list<Keyboard::Key> InputMgr::keyList;

void InputMgr::Init()
{
    // Horizontal
    AxisInfo info;
    info.axis = Axis::Horizontal;
    info.positives.push_back(Keyboard::Key::D);
    info.positives.push_back(Keyboard::Key::Right);
    info.negatives.push_back(Keyboard::Key::A);
    info.negatives.push_back(Keyboard::Key::Left);
    axisInfoMap.insert({ info.axis, info });

    // Vertical
    info.axis = Axis::Vertical;
    info.positives.push_back(Keyboard::Key::S);
    info.positives.push_back(Keyboard::Key::Down);
    info.negatives.push_back(Keyboard::Key::W);
    info.negatives.push_back(Keyboard::Key::Up);
    axisInfoMap.insert({ info.axis, info });
}

void InputMgr::ClearInput()
{
    for (auto key : keyList)
    {
        downList[key] = false;
    }
    for (auto key : keyList)
    {
        upList[key] = false;
    }
    keyList.clear();
}

void InputMgr::UpdateInput(const Event& ev)
{
    switch (ev.type)
    {
    case Event::EventType::KeyPressed:
        if (ev.key.code != Keyboard::Key::Unknown && !GetKey(ev.key.code))
        {
            keyList.push_back(ev.key.code);
            downList[ev.key.code] = true;
            ingList[ev.key.code] = true;
        }
        break;
    case Event::EventType::KeyReleased:
        if (ev.key.code != Keyboard::Key::Unknown)
        {
            keyList.push_back(ev.key.code);
            ingList[ev.key.code] = false;
            upList[ev.key.code] = true;
        }
        break;
    }
}

bool InputMgr::GetKeyDown(Keyboard::Key key)
{
    return downList[key];
}

bool InputMgr::GetKey(Keyboard::Key key)
{
    return ingList[key];
}

bool InputMgr::GetKeyUp(Keyboard::Key key)
{
    return upList[key];
}

float InputMgr::GetAxisRaw(Axis axis)
{
    const AxisInfo& info = axisInfoMap[axis];
    for (auto key : info.negatives)
    {
        if (GetKey(key))
            return -1.f;
    }
    for (auto key : info.positives)
    {
        if (GetKey(key))
            return 1.f;
    }
    return 0;
}
