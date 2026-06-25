#include "stdafx.h"
#include "CountUI.h"
#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include"Result1.h"
CountUI::CountUI()
{
	fontRender.SetColor(g_vec4Black);
	position = { -930.0f, 450.0f, 0.0f };
}

CountUI::~CountUI()
{

}

void CountUI::Update()
{
	// ゲームがアクティブでない間は時間を進めない
	if (g_IsGameActive)
	{
		// 毎フレーム経過時間を加算
		elapsedTime += g_gameTime->GetFrameDeltaTime();
	}

	wchar_t text[256];
	swprintf_s(text, 256, L"手に入れたクリスタルの数:%d個", UInum);
	fontRender.SetText(text);
	fontRender.SetPosition(position);
	player = FindGO<Player>("player");
	// 経過時間の「秒部分」ではなく、累積の経過秒数を使う
	int totalSeconds = (int)elapsedTime;
	if (totalSeconds < 1) totalSeconds = 1; // ゼロ除算回避
	// 既存の係数(50 と *5)を維持して合算した形で計算する
	Score = (player->crystalCount * 250) / totalSeconds;
}

void CountUI::Render(RenderContext& rc)
{
	fontRender.Draw(rc);
}