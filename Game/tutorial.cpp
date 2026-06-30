#include "stdafx.h"
#include "Tutorial.h"
#include"Game.h"
#include "sound/SoundEngine.h"
#include"Title.h"
Tutorial::Tutorial()
{
	spriteRender.Init("Assets/sprite/tutorial.dds", 1920.0f, 1080.0f);
	fontRender.SetColor(g_vec4Black);
	fontRender.SetPosition({ -800.0f,400.0f,0.0f });
	fontRender.SetScale(2.0f);
	
}
Tutorial::~Tutorial() {

}
void Tutorial::Update()
{
	wchar_t text[256];
	swprintf_s(text, 256, L"           ゲーム説明\n\n動き回るクリスタルをできるだけ短時間で\nたくさん集めてゴールしよう！\n\nクリスタルを３個以上集めると\nゴールが現れるぞ！\n\n\n          　　　　　Aボタンでゲーム開始");
	fontRender.SetText(text);
	
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0);
		DeleteGO(this);
	}
	//Bキーを押されたらスタート画面に戻る
	if (g_pad[0]->IsTrigger(enButtonLB1)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
	//7が押されたらゲームを終了する
	if (g_pad[0]->IsTrigger(enButtonRB1)) {	
		exit(0);
	}
}
void Tutorial::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	fontRender.Draw(rc);
}