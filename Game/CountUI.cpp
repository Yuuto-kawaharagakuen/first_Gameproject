#include "stdafx.h"
#include "CountUI.h"
#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include"Result1.h"
CountUI::CountUI()
{
	fontRender.SetColor(g_vec4Black);
	position = { -860.0f, 420.0f, 0.0f };
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

	wchar_t text[50];
	swprintf_s(text, 50, L"x%d", UInum);
	fontRender.SetText(text);
	fontRender.SetPosition(position);
	player = FindGO<Player>("player");
	// 経過時間の「秒部分」ではなく、累積の経過秒数を使う
	int totalSeconds = (int)elapsedTime;
	if (totalSeconds < 1) totalSeconds = 1; // ゼロ除算回避
	
	Score = player->crystalCount * 1000 + 10000-totalSeconds*30;

	if (Score <= 0) {
		Score = 0;
	}
}

void CountUI::Render(RenderContext& rc)
{
	fontRender.Draw(rc);
}