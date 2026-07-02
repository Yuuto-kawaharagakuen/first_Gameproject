#include "stdafx.h"
#include "GoalUI.h"
GoalUI::GoalUI() {
	fontRender.SetColor(g_vec4Black);
	position = { -300.0f, 300.0f, 0.0f };
}

GoalUI::~GoalUI()
{

}
void GoalUI::Update() {
	if (position.y < 360.0f) {
		position.y += 0.25f;
		// 目標位置に到達したらタイマー開始
		if (position.y >= 360.0f && displayTimer < 0.0f) {
			displayTimer = 5.0f; // 5秒間表示
			visible = true;
		}
	}

	// タイマーが動作中なら減算
	if (displayTimer >= 0.0f) {
		// 固定60FPS想定
		displayTimer -= 1.0f / 60.0f;
		if (displayTimer <= 0.0f) {
			// 表示終了
			visible = false;
			displayTimer = -1.0f;
		}
	}

	wchar_t text[25];
	if (visible) {
		swprintf_s(text, 25, L"屋上にゴールが出現しました!");
		fontRender.SetText(text);
	} 
	else {
		// 空文字をセットして描画させない
		fontRender.SetText(L"");
	}
	fontRender.SetPosition(position);
}

void GoalUI::Render(RenderContext& rc)
{
		fontRender.Draw(rc);
}