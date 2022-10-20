#include "Framework.h"
#include "InputMgr.h"
#include "../Scene/SceneMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"

Framework::Framework(int width, int height)
	:windowSize(width, height), timeScale(1.f)
{
	window.create(VideoMode(windowSize.x, windowSize.y), "Game");
}

Framework::~Framework()
{

}

float Framework::GetDT() const
{
    return deltaTime.asSeconds() * timeScale;
}

float Framework::GetRealDT() const
{
    return deltaTime.asSeconds();
}

bool Framework::Init()
{
    RESOURCE_MGR->LoadAll();
    DATATABLE_MGR->Init();
    SOUND_MGR->Init();
    SCENE_MGR->Init();
    InputMgr::Init();
    return true;
}

bool Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = clock.restart();
        float dt = GetDT();

        InputMgr::ClearInput();
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateInput(ev);
        }
        SCENE_MGR->Update(dt);
        window.clear();
        SCENE_MGR->Draw(window);
        window.display();
    }
    return true;
}
