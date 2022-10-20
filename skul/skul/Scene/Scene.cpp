#include "Scene.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Ui/UiMgr.h"

Scene::Scene(Scenes type)
	: type(type)
{
}

Scene::~Scene()
{
	Release();
	
}
void Scene::Release()
{
	for (const auto& obj : objList)
	{
		if (obj->GetActive())
		{
			obj->Release();
			delete obj;
		}
	}
	objList.clear();
}

void Scene::Enter()
{
	worldView.setCenter((Vector2f)FRAMEWORK->GetWindowSize() * 0.5f);
	worldView.setSize((Vector2f)FRAMEWORK->GetWindowSize());
}

void Scene::Update(float dt)
{
	for (const auto& obj : objList)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	for (const auto& obj : objList)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

}

Texture* Scene::GetTexture(const string path) const
{
	return RESOURCE_MGR->GetTexture(path);
}

Vector2f Scene::ScreenToWorld(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, worldView);
}

Vector2f Scene::ScreenToUiPosition(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos,uiView);
}

void Scene::AddGameObject(Object* obj)
{
	objList.push_back(obj);
}
void Scene::AddGameObjectFirst(Object* obj)
{
	objList.insert(++objList.begin(), obj);
}
void Scene::DelGameObject(Object* obj)
{
	objList.remove(obj);
}

Object* Scene::FindGameObj(string name)
{
	for (auto *obj : objList)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}
