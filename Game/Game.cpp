#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include"Crystal.h"
#include "sound/SoundEngine.h"
#include"GameClear.h"
#include"Result1.h"
#include"Title.h"
#include "CountUI.h"
#include"Goal.h"
#include"GoalUI.h"
#include "GameState.h"
#include "Countdown.h"
#include"MoveCrystal1.h"
#include"EscapeCrystal.h"

Game::Game()
{   //背景を生成
	sky = NewGO<SkyCube>(0, "skycube");
	sky->SetType(enSkyCubeType_DayToon);
	g_renderingEngine->SetAmbientByIBLTexture(sky->GetTextureFilePath(), 0.75f);

	//プレイヤーのオブジェクトを作る
	player = NewGO<Player>(0, "player");
	//ゲームカメラのオブジェクトを作る
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る
	backGround = NewGO<BackGround>(0);

	//UIを生成
	countUI = NewGO<CountUI>(0,"countUI");
	//ここでgoalUIをnullptrにしておく。これで、ゲーム開始時にはゴールUIは存在しない状態になる。
	goalUI = nullptr;
	goalUIElapsedTime = 0.0f;
	float crystal4X = GetRandomValue(-1250.0f, 450.0f);
	float crystal4Z = GetRandomValue(-1150.0f, -800.0f);
	float crystal5X = GetRandomValue(-1450.0f, -600.0f);
	float crystal5Z = GetRandomValue(-700.0f, 300.0f);
	float crystal6X = GetRandomValue(350.0f, 1000.0f);
	float crystal6Z = GetRandomValue(-500.0f, 300.0f);
	float crystal8Z = GetRandomValue(-1500.0f, 2000.0f);
	float crystal10X = GetRandomValue(-120.0f, 1000.0f);
	//Starクラスのオブジェクトを作る
	Crystal* crystal1 = NewGO<Crystal>(0, "crystal");
	crystal1->position = { 1130.0f,1553.2f,-1120.5f };
	crystal1->firstPosition = crystal1->position;
	
	Crystal* crystal2 = NewGO<Crystal>(0, "crystal");
	crystal2->position = { 144.3f,286.3f,-984.9f };
	crystal2->firstPosition = crystal2->position;

	Crystal* crystal3 = NewGO<Crystal>(0, "crystal");
	crystal3->position = { 1450.0f,30.7f,-1450.0f };
	crystal3->firstPosition = crystal3->position;

	Crystal* crystal4 = NewGO<Crystal>(0, "crystal");
	crystal4->position = { crystal4X,-300.0f,crystal4Z };
	crystal4->firstPosition = crystal4->position;

	Crystal* crystal5 = NewGO<Crystal>(0, "crystal");
	crystal5->position = { crystal5X,-30.03f,crystal5Z };
	crystal5->firstPosition = crystal5->position;
	
	Crystal* crystal6 = NewGO<Crystal>(0, "crystal");
	crystal6->position = { crystal6X,10.40f, crystal6Z };
	crystal6->firstPosition = crystal6->position;

	Crystal* crystal7 = NewGO<Crystal>(0, "crystal");
	crystal7->position = { 1000.0f,10.39f,-1000.0f };
	crystal7->firstPosition = crystal7->position;

	Crystal* crystal8 = NewGO<Crystal>(0, "crystal");
	crystal8->position = { -1685.0f,10.0f, crystal8Z };
	crystal8->firstPosition = crystal8->position;

	Crystal* crystal9 = NewGO<Crystal>(0, "crystal");
	crystal9->position = { 1250.0f,623.0f, -700.0f };
	crystal9->firstPosition = crystal9->position;

	Crystal* crystal10 = NewGO<Crystal>(0, "crystal");
	crystal10->position = { 500.0f,285.3f,900.0f };
	crystal10->firstPosition = crystal10->position;

	MoveCrystal1* moveCrystal1 = NewGO<MoveCrystal1>(0, "crystal");
	moveCrystal1->position = { 0.0f,-300.0f,1200.0f };
	moveCrystal1->firstPosition = moveCrystal1->position;

	EscapeCrystal* escapeCrystal = NewGO<EscapeCrystal>(0, "crystal");
	escapeCrystal->position = { 600.0f,1010.0f,-150.0f };
	escapeCrystal->firstPosition = escapeCrystal->position;

	goal = NewGO<Goal>(0, "goal");
	goal->position = { 50000.0f, 5000.0f, 5000.0f };
	//ゲーム中のBGMを読み込む
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Gamebgm.wav");
    //ゲーム中のBGMを再生する
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(1);
	gameBGM->Play(true);

	// カウントダウン用オブジェクトを作る（この中でカウントが終わると g_IsGameActive = true になる）
	NewGO<Countdown>(0, "countdown");

	spriteRender.Init("Assets/sprite/crystal.dds", 150.0f, 100.0f);
	spriteRender.SetPosition({ -900.0f, 410.0f, 0.0f });

	//画面全体を暗くする半透明画像（黒一色のdds）
	m_pauseOverlaySprite.Init("Assets/sprite/halfblack.dds", 5760.0f,3024.0f);
	m_pauseOverlaySprite.SetPosition({ 0.0f,0.0f,0.0f });

	//中央パネル
	m_pausePanelSprite.Init("Assets/sprite/black.dds",1920.0f/2,1080.0f/2);
	m_pausePanelSprite.SetPosition({ 0.0f, 0.0f, 0.0f });


	m_pauseTitleText.SetText(L"ポーズ");
	m_pauseTitleText.SetPosition({ -80.0f,100.0f,0.0f});
	
	m_pauseOption1Text.SetText(L"つづける");
	m_pauseOption1Text.SetPosition({ -100.0f,30.0f,0.0f});
	
	m_pauseOption2Text.SetText(L"タイトルへ");
	m_pauseOption2Text.SetPosition({ -100.0f,-30.0f,0.0f});

	m_pauseCursorText.SetText(L"＞");
	m_pauseCursorText.SetPosition(m_pauseCursorX,m_pauseCursorPosOption1Y,0.0f); // 初期は「つづける」を指す

}

Game::~Game()
{
	for (auto crystal : FindGOs<Crystal>("crystal")) {
		//この星を消すッ！
		DeleteGO(crystal);
		DeleteGO(goal);
	}
	for (auto crystal : FindGOs<MoveCrystal1>("crystal")) {
		//この星を消すッ！
		DeleteGO(crystal);
	}
	for (auto crystal : FindGOs<EscapeCrystal>("crystal")) {
		//この星を消すッ！
		DeleteGO(crystal);
	}
		//プレイヤーを削除する。
	DeleteGO(player);
	//ゲームカメラを削除する。
	DeleteGO(gameCamera);
	//ゲーム中のBGMを削除する。
	DeleteGO(gameBGM);
	//背景を削除する。
	DeleteGO(backGround);
	//UIを削除する
	DeleteGO(countUI);
	//ゴールUIを削除する;
	DeleteGO(goalUI);

}

//更新処理
void Game::Update()
{
	spriteRender.Update();

	//Bキーを押されたらスタート画面に戻る
	if (g_pad[0]->IsTrigger(enButtonRB1)) {
		if (!m_isPaused) EnterPause();
		else ExitPause(false);
	}

	if (m_isPaused) {
		UpdatePauseMenu();
		return;
	}

	if (player->crystalCount >= 5) {
		//goalUIがnullptr(中身が空)のときにゴールを生成
		if (!goalUI) {
			goal->position = { 570.0f, 967.1f, 600.0f };
			goalUI = NewGO<GoalUI>(0, "goalUI");
		}
	}
	if (goal->getGoal==true) {
		if (gameBGM) {
			gameBGM->Stop();
			gameBGM->Release();
			gameBGM = nullptr;
		}
		// ゴール処理: Result画面に遷移
		GameClear* gameClear = NewGO<GameClear>(0, "gameClear");
		// 経過時間とスコアを渡す
		gameClear->SetElapsedTime(countUI->GetElapsedTime());
		gameClear->SetScore(countUI->Score);
		// ゲームオブジェクトを削除
		DeleteGO(goalUI);
		DeleteGO(this);
	}
	
	//7が押されたらゲームを終了する
	/*if (g_pad[0]->IsTrigger(enButtonRB1)) {
		exit(0);
	}*/
}

void Game::EnterPause() {
	m_isPaused = true;
	m_gameActiveBeforePause = g_IsGameActive;
	g_IsGameActive = false;
	m_pauseCursor = 0;
	m_pauseCursorText.SetPosition(m_pauseCursorX,m_pauseCursorPosOption1Y,0.0f);
}

void Game::ExitPause(bool backToTitle) {
	if (backToTitle) {
		if (gameBGM) {
			gameBGM->Stop();
			gameBGM->Release();
			gameBGM = nullptr;
		}
		NewGO<Title>(0, "title");
		DeleteGO(this);
		return;
	}

	m_isPaused = false;
	g_IsGameActive = m_gameActiveBeforePause;

}

void Game::UpdatePauseMenu() {
	if (g_pad[0]->IsTrigger(enButtonUp) or g_pad[0]->IsTrigger(enButtonDown)) {

		m_pauseCursor = (m_pauseCursor == 0) ? 1 : 0;
		m_pauseCursorText.SetPosition(m_pauseCursorX,(m_pauseCursor == 0) ? m_pauseCursorPosOption1Y : m_pauseCursorPosOption2Y,0.0f);

	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		ExitPause(m_pauseCursor == 1);
	}
}

void Game::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);

	if (m_isPaused) {
		DrawPauseMenu(rc);
	}
}

void Game::DrawPauseMenu(RenderContext& rc) {

	m_pauseOverlaySprite.Draw(rc);
	m_pausePanelSprite.Draw(rc);
	m_pauseTitleText.Draw(rc);
	m_pauseCursorText.Draw(rc);
	m_pauseOption1Text.Draw(rc);
	m_pauseOption2Text.Draw(rc);

}