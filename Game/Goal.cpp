#include "stdafx.h"
#include "Goal.h"
#include"Player.h"
#include "GameState.h"
Goal::Goal() {
	modelRender.Init("Assets/modelData/Flag.tkm");
	player = FindGO<Player>("player");
}
Goal::~Goal() {

}

void Goal::Update() {
	//絵描きさんの更新処理
	modelRender.Update();
	modelRender.SetPosition(position);
	modelRender.SetScale(Vector3(5.0f, 5.0f, 5.0f));
	rot.SetRotationDegY(-180.0f);
	modelRender.SetRotation(rot);
	// プレイヤーが接触してゴールする処理はゲームアクティブ時のみ行う
	if (g_IsGameActive)
	{
		//プレイヤーから☆に向かうベクトルを計算。
		Vector3 diff = player->position - position;

		if (diff.Length() <= 150.0f) {
			// すでにゴールしていなければ一度だけ処理する
			if (!getGoal) {
				//効果音の再生
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(2);
				se->SetVolume(3.5f);
				se->Play(false);
				getGoal = true;
			}
		}
	}
}

void Goal::Render(RenderContext& rc) {
	modelRender.Draw(rc);
}
