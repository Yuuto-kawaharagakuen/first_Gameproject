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
	g_renderingEngine->SetAmbientByIBLTexture(sky->GetTextureFilePath(), 0.8f);

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
	crystal4->position = { 0.0f,90000.0f,0.0f };
	crystal4->firstPosition = crystal4->position;

	Crystal* crystal5 = NewGO<Crystal>(0, "crystal");
	crystal5->position = { 0.0f,90000.0f,0.0f };
	crystal5->firstPosition = crystal5->position;

	Crystal* crystal6 = NewGO<Crystal>(0, "crystal");
	crystal6->position = { 0.0f,90000.0f,0.0f };
	crystal6->firstPosition = crystal6->position;

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

	if (player->crystalCount >= 3) {
		//goalUIがnullptr(中身が空)のときにゴールを生成
		if (!goalUI) {
			goal->position = { 823.5f, 967.1f, -279.9f };
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
	//Bキーを押されたらスタート画面に戻る
	if (g_pad[0]->IsTrigger(enButtonLB1)) {
		NewGO<Title>(0,"title");
		DeleteGO(this);
	}
	//7が押されたらゲームを終了する
	if (g_pad[0]->IsTrigger(enButtonRB1)) {
		exit(0);
	}
}
