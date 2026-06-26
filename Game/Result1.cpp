#include "stdafx.h"
#include "Result1.h"
#include"Title.h"
#include"sound/SoundEngine.h"
Result1::Result1() {
	//ゲームクリアの画像を読み込む
	spriteRender.Init("Assets/sprite/result.dds",1920.0f,1080.0f);
	//フォント表示の初期化
	fontRender.SetPosition({ -800.0f,150.0f,0.0f});
	fontRender.SetColor(g_vec4Black);
	fontRender.SetScale(2.0f);
	// スコア表示用フォント初期化
	scoreRender.SetPosition({ -600.0f,-50.0f,0.0f });
	scoreRender.SetColor(g_vec4Black);
	scoreRender.SetScale(2.0f);
	//リザルト画面のBGMを読み込む
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/result.wav");
	//リザルト画面のBGMを再生する。
	ResultBGM = NewGO<SoundSource>(0);
	ResultBGM->Init(4);
	ResultBGM->Play(true);
}

Result1::~Result1() {

}
//更新処理
void Result1::Update() {
	//クリア時間をフォント表示
	int minutes = (int)elapsedTime / 60;
	int seconds = (int)elapsedTime % 60;
	wchar_t text[256];
	swprintf_s(text, 256, L"あなたのクリア時間: %d分:%02d秒", minutes, seconds);
	fontRender.SetText(text);

	// スコア表示更新
	wchar_t scoreText[256];
	swprintf_s(scoreText, 256, L"あなたのスコア: %d", score);
	scoreRender.SetText(scoreText);

	//Aボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {
		// BGM を止めて解放する
		if (ResultBGM) {
			ResultBGM->Stop();
			ResultBGM->Release();
			ResultBGM = nullptr;
		}
		//タイトルのオブジェクトを作る
		NewGO<Title>(0, "title");
		//自身を削除する
		DeleteGO(this);
	}
	//Bキーを押されたらスタート画面に戻る
	if (g_pad[0]->IsTrigger(enButtonLB1)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}
//描画処理
void Result1::Render(RenderContext& rc) {
	spriteRender.Draw(rc);
	fontRender.Draw(rc);
	// スコアも描画する（経過時間と同じタイミングで表示される）
	scoreRender.Draw(rc);
}