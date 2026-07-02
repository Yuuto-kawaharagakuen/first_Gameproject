#include "stdafx.h"
#include "MoveCrystal1.h"
#include "GameState.h"
#include"Player.h"
#include "sound/SoundEngine.h"
#include"sound/SoundSource.h"
#include"CountUI.h"
#include<time.h>
MoveCrystal1::MoveCrystal1() {
	//☆のモデルを読み込む。
	modelRender.Init("Assets/modelData/blueObject.tkm");

	player = FindGO<Player>("player");

	//☆を削除するときの音を読み込む
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/get.wav");

	// 初期化
	isStopped = false;
	stopTimer = 0.0f;
	prevXDown = false;
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

	//移動処理。
	if (cooldownTimer <= 0.0f && g_pad[0]->IsTrigger(enButtonY))
	{
		isStopped = true;
		stopTimer = 3.0f; // 3秒
		cooldownTimer = 30.0f;
	}

	// 停止中は移動・回転を行わない
	if (!isStopped)
	{
		Move();
		//回転処理。
		Rotation();
	}
	else
	{
		stopTimer -= 1.0f / 60.0f;
		if (stopTimer <= 0.0f)
		{
			isStopped = false;
		}
	}

	if (cooldownTimer > 0.0f)
	{
		cooldownTimer -= 1.0f / 60.0f;
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
		//自身を削除する。
		DeleteGO(this);
	}
}

void MoveCrystal1::Move()
{
	srand(time(nullptr));
	position.x += rand() % 30;
	position.x -= rand() % 30;
	position.z += rand() % 30;
	position.z -= rand() % 30;
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

	/*if (moveCount == 0)
	{
		position.y += 1.0f;
	}

	else if (moveCount == 1)
	{
		position.y -= 1.0f;
	}
	if (position.y >= firstPosition.y + 50.0f)
	{
		moveCount = 1;
	}

	else if (position.y <= firstPosition.y - 50.0f)
	{
		moveCount = 0;
	}*/

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
	fontRender.Draw(rc);
}