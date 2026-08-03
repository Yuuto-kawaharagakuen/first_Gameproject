#include "stdafx.h"
#include "GoalUI.h"
GoalUI::GoalUI() {
	fontRender.SetColor(g_vec4Black);
	position = { -300.0f, 330.0f, 0.0f };
}

GoalUI::~GoalUI()
{

}
void GoalUI::Update() {
	wchar_t text[20];
	swprintf_s(text, 20, L"ゴールが出現しました!");
	fontRender.SetText(text);
	fontRender.SetPosition(position);
}

void GoalUI::Render(RenderContext& rc)
{
		fontRender.Draw(rc);
}