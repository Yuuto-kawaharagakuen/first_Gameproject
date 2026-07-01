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
	wchar_t text[25];
	swprintf_s(text, 25, L"屋上にゴールが出現しました!");
	fontRender.SetText(text);
	fontRender.SetPosition(position);
}

void GoalUI::Render(RenderContext& rc)
{
		fontRender.Draw(rc);
}