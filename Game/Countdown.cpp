#include "stdafx.h"
#include "Countdown.h"
#include "GameState.h"

Countdown::Countdown()
{
	elapsed = 0.0f;
	currentCount = 3;
	fontRender.SetScale(4.0f);
	fontRender.SetColor(g_vec4White);
}

Countdown::~Countdown()
{

}

void Countdown::Update()
{
	// カウントダウン中はゲームを停止
	g_IsGameActive = false;

	elapsed += g_gameTime->GetFrameDeltaTime();

	// 1秒ごとにカウントを減らす
	if (elapsed >= 1.0f)
	{
		elapsed = 0.0f;
		currentCount--;
		if (currentCount < 0)
		{
			// カウントダウン終了
			g_IsGameActive = true;
			DeleteGO(this);
			return;
		}
	}
}

void Countdown::Render(RenderContext& rc)
{
	wchar_t buf[32];
	if (currentCount > 0)
	{
		swprintf_s(buf, L"%d", currentCount);
	}
	else
	{
		swprintf_s(buf, L"Start!");
	}
	fontRender.SetText(buf);
	fontRender.SetPosition({ -140.0f, 400.0f, 0.0f });
	fontRender.Draw(rc);
}
