#include "stdafx.h"
#include "EscapeCrystal.h"
#include "GameState.h"
#include"Player.h"
#include "sound/SoundEngine.h"
#include"sound/SoundSource.h"
#include"CountUI.h"
EscapeCrystal::EscapeCrystal() {
	//☆のモデルを読み込む。
	modelRender.Init("Assets/modelData/blueObject.tkm");

	player = FindGO<Player>("player");

	//☆を削除するときの音を読み込む
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/get.wav");

	// 初期化
	isStopped = false;
	stopUsed = false;
	stopTimer = 0.0f;
	prevXDown = false;
}

EscapeCrystal::~EscapeCrystal()
{

}

void EscapeCrystal::Update()
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
	// Xボタンで一度だけ3秒間停止させる処理
	if (!stopUsed && g_pad[0]->IsTrigger(enButtonX))
	{
		isStopped = true;
		stopUsed = true; // 一度だけ
		stopTimer = 3.0f; // 3秒
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
		// 固定フレームレート(60FPS)を想定してタイマーを減算
		stopTimer -= 1.0f / 60.0f;
		if (stopTimer <= 0.0f)
		{
			isStopped = false;
		}
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

void EscapeCrystal::Move()
{
	if (position.x >= 1200) {
		position.x =rand()% 450+600;
	}
	if (position.x <= 500) {

		position.x = rand()% 450 + 600;
	}
	if (position.z >= 320) {

		position.z = rand()% 800- 950;
	}
	if (position.z <= -1000) {
		position.z = rand()% 800-700;
	}

	// プレイヤーから常に200.0fの距離を保つ処理
	Vector3 toPlayer = position - player->position;
	float distance = toPlayer.Length();
	if (toPlayer.Length()<=200.0f) {
		if (distance > 0.0f && distance != 200.0f)
		{
			toPlayer.Normalize();
			Vector3 newPosition = player->position + toPlayer * 200.0f;
			// y座標は変更しない
			position.x = newPosition.x;
			position.z = newPosition.z;
		}
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
void EscapeCrystal::Rotation()
{
	rotation.AddRotationDegY(2.0f);

	modelRender.SetRotation(rotation);
}

void EscapeCrystal::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
	fontRender.Draw(rc);
}