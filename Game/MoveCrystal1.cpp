#include "stdafx.h"
#include "MoveCrystal1.h"
#include "GameState.h"
#include"Player.h"
#include "sound/SoundEngine.h"
#include"sound/SoundSource.h"
#include"CountUI.h"
#include<time.h>
#include"PopupText.h"

MoveCrystal1::MoveCrystal1() {
	//☆のモデルを読み込む。
	modelRender.Init("Assets/modelData/blueObject.tkm");

	player = FindGO<Player>("player");

	//☆を削除するときの音を読み込む
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/get.wav");
}

MoveCrystal1::~MoveCrystal1()
{

}

void MoveCrystal1::Update()
{
	// ゲームがアクティブでない間は動作しない
	if (g_IsGameActive == false)
	{
		//描画はする
		modelRender.SetPosition(position);
		modelRender.SetRotation(rotation);
		modelRender.Update();
		return;
	}

	// プレイヤーのフリーズスキルで止められていなければ移動・回転する
	if (!player->isStopped)
	{
		Move();
		Rotation();
	}

	//絵描きさんの更新処理。
	modelRender.Update();

	//プレイヤーから☆に向かうベクトルを計算。
	Vector3 diff = player->position - position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{
		//効果音を再生する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->SetVolume(3.5f);
		se->Play(false);
		CountUI* countUI = FindGO<CountUI>("countUI");
		countUI->UInum += 1;
		player->crystalCount += 1;

		PopupText* popup = NewGO<PopupText>(0);
		popup->Init(L"+1");
		//自身を削除する。
		DeleteGO(this);
	}
}

void MoveCrystal1::Move()
{
	srand(time(nullptr));
	position.x += rand() % 15;
	position.x -= rand() % 15;
	position.z += rand() % 15;
	position.z -= rand() % 15;
	if (position.x >= 1065) {
		position.x = rand() % 2000 - 1000;
	}
	if (position.x <= -1315) {
		position.x = rand() % 2000 - 1000;
	}
	if (position.z >= 1870) {
		position.z = rand() % 1050 + 600;
	}
	if (position.z <= 590) {
		position.z = rand() % 1350 + 600;
	}

	modelRender.SetPosition(position);
}

//回転処理
void MoveCrystal1::Rotation()
{
	rotation.AddRotationDegY(2.0f);

	modelRender.SetRotation(rotation);
}

void MoveCrystal1::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}