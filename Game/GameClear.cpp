#include "stdafx.h"
#include "GameClear.h"
#include "Result1.h"
#include "Title.h"
#include"sound/SoundEngine.h"
GameClear::GameClear() {
	// GameClearではゲームクリアの画像のみを表示
	spriteRender.Init("Assets/sprite/gameclear1.dds", 1920.0f, 1080.0f);

	fontRender.SetPosition({ 350.0f,530.0f,0.0f });
	fontRender.SetColor(g_vec4Black);
	fontRender.SetText(L"NEXT-リザルトへ");
	fontRender.SetScale(1.5f);
	// ゲームクリアのBGMを読み込む
	g_soundEngine->ResistWaveFileBank(3,"Assets/sound/GameClear.wav");
	GameClearBGM = NewGO<SoundSource>(0);
	GameClearBGM->Init(3);
	GameClearBGM->Play(false);
}

GameClear::~GameClear() 
{
}

void GameClear::Update() {
	// Aボタンが押されたら Result1 に移動し、経過時間とスコアを渡す
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Result1* r1 = NewGO<Result1>(0, "result1");
		r1->SetElapsedTime(elapsedTime);
		r1->SetScore(score);
		DeleteGO(this);
	}

	// Bボタンでタイトルへ戻る
	if (g_pad[0]->IsTrigger(enButtonRB1)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
	//7が押されたらゲームを終了する
	/*if (g_pad[0]->IsTrigger(enButtonRB1)) {
		exit(0);
	}*/
}

void GameClear::Render(RenderContext& rc) {
	spriteRender.Draw(rc);
	fontRender.Draw(rc);
}
