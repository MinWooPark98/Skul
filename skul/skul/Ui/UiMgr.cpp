#include "UiMgr.h"

UiMgr::UiMgr(Scene* scene) : parentScene(scene)
{
}

UiMgr::~UiMgr()
{
}

void UiMgr::Init()
{
    for (auto uiObj : uiObjList)
	{
		uiObj->Init();
	}
	Object::Init();
}

void UiMgr::Release()
{
	for (auto uiObj : uiObjList)
	{
		uiObj->Release();
	}
	Object::Release();
}

void UiMgr::Reset()
{
    for (auto uiObj : uiObjList)
    {
        uiObj->Reset();
    }
    Object::Reset();
}

void UiMgr::SetPos(const Vector2f& pos)
{
    Vector2f delta = pos - position;
    for (auto uiObj : uiObjList)
    {
        uiObj->Translate(delta);
    }
    position = pos;
    Object::SetPos(pos);
}

void UiMgr::Update(float dt)
{
    if (!enabled)
        return;
    for (auto uiObj : uiObjList)
    {
        if(uiObj->GetActive())
            uiObj->Update(dt);
    }
}

void UiMgr::Draw(RenderWindow& window)
{
    if (!enabled)
        return;
    for (auto uiObj : uiObjList)
    {   
        if (uiObj->GetActive())
            uiObj->Draw(window);
    }
}

Object* UiMgr::FindUiObj(string name)
{
    for (auto* obj : uiObjList)
    {
        if (obj->GetName() == name)
        {
            return obj;
        }
    }
    return nullptr;
}
