#include "TextButtons.h"
#include "TextObj.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Framework/InputMgr.h"

TextButtons::TextButtons()
	:vecIdx(0), textSize(30), buttonDistance(0.f)
{
}

TextButtons::~TextButtons()
{
}

void TextButtons::AddButton(const string& text)
{
	TextObj* newButton = new TextObj();
	newButton->Init();
	newButton->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	newButton->SetSize(textSize);
	newButton->SetText(text);
	newButton->SetOrigin(Origins::MC);
	newButton->SetPos({ position.x, position.y + (textSize + buttonDistance) * buttons.size() });
	if (buttons.empty())
		newButton->SetFillColor({ 255, 255, 255, 255 });
	else
		newButton->SetFillColor({ 255, 255, 255, 150 });
	buttons.push_back(newButton);

}

void TextButtons::SetCharacterSize(int size)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->SetSize(size);
		buttons[i]->SetPos({ position.x, position.y + (textSize + buttonDistance) * i });
	}
}

void TextButtons::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Up) && vecIdx > 0)
	{
		buttons[vecIdx]->SetFillColor({ 255, 255, 255, 150 });
		vecIdx -= 1;
		buttons[vecIdx]->SetFillColor({ 255, 255, 255, 255 });
	}
	else if (InputMgr::GetKeyDown(Keyboard::Down) && vecIdx < buttons.size() - 1)
	{
		buttons[vecIdx]->SetFillColor({ 255, 255, 255, 150 });
		vecIdx += 1;
		buttons[vecIdx]->SetFillColor({255, 255, 255, 255});
	}
}

void TextButtons::Draw(RenderWindow& window)
{
	for (auto button : buttons)
	{
		button->Draw(window);
	}
}
