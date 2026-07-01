#include "stdafx.h"
#include"Game.h"
#include "GameState.h"
#include "Player.h"
Player::Player()
{
	position = { -1700.0f,-43.88f,450.0f };
	//アニメーションクリップをロードする
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	fontRender.SetColor(g_vec4Black);
	//ユニティちゃんのモデルを読み込む
	modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
	// 初期の向き
	rotation.SetRotationDeg(Vector3::AxisY, 90.0f);
	modelRender.SetRotation(rotation);

	//キャラコンを初期化する
	characterController.Init(25.0f, 75.0f, position);
}

Player::~Player() 
{

}

//更新処理
void Player::Update() 
{
	// ゲームがアクティブでない間は動作しない（カウントダウン中）
	if (g_IsGameActive == false)
	{
		// レンダリングに必要な最低限の更新を行う
		modelRender.SetPosition(position);
		modelRender.SetRotation(rotation);
		modelRender.Update();
		return;
	}

	//移動処理
	Move();

	//回転処理
	Rotation();

	//ステート管理
	ManageState();

	//アニメーションの再生
	PlayAnimation();

	//wchar_t text[128];
	//	swprintf_s(text, 128, L"X: %.2f Y: %.2f Z: %.2f", position.x, position.y, position.z);
	//	fontRender.SetText(text);
	//絵描きさんの更新処理
	modelRender.Update();
}

void Player::Move() 
{
	//xzの移動速度を0.0fにする
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と240.0fを乗算
	right *= stickL.x * 240.0f;
	forward *= stickL.y * 240.0f;

	//移動速度にスティックの入力量を加算する
	moveSpeed += right + forward;

	moveSpeed.y -= 10.0f;
	//Aボタンが押されたら移動速度2.5倍
	if (g_pad[0]->IsPress(enButtonB)) {
		moveSpeed.x *= 2.5;
		moveSpeed.z *= 2.5;
	}
	//地面についていたら
	if (characterController.IsOnGround())
	{
		//重力をなくす
		moveSpeed.y = 0.0f;
		jumpState = 0;
		//Bボタンが押されたら
		if(g_pad[0]->IsTrigger(enButtonA))
		{
		//ジャンプさせる
			moveSpeed.y = 580.0f;	
		}
	}
	else if (characterController.IsOnGround() == false) {

		if (g_pad[0]->IsTrigger(enButtonA) and jumpState == 0)
		{
			modelRender.PlayAnimation(enAnimationClip_Idle);
			moveSpeed.y = 580.0f;
			jumpState = 1;
		}
	}

	//マップ外に落下したら

	if (position.y <= -1000.0f)
	{
		position= { -1700.0f,-43.88f,450.0f };

		characterController.SetPosition(position);
	}
	//キャラクターコントローラーを使って座標を移動させる
	position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える
	modelRender.SetPosition(position);
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)
	if (fabsf(moveSpeed.x) >= 0.001f or fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		//絵描きさんに回転を教える
		modelRender.SetRotation(rotation);
	}
}

//ステート管理
void Player::ManageState()
{
	//地面についていなかったら
	if (characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする
		playerState = 1;
		//ここでManageStateの処理を終わらせる
		return;
	}
	//Bボタンを押しているときかつ、動いているとき
	if (g_pad[0]->IsPress(enButtonB) and (fabsf(moveSpeed.x) >= 0.001f or fabsf(moveSpeed.z) >= 0.001f)) {
		playerState = 3;
	}

	//地面についていたら
	//xかzの移動速度があったら(スティックの入力があったら)
	else if (fabsf(moveSpeed.x) >= 0.001f or fabsf(moveSpeed.z) >= 0.001f) {
		//ステートを2(歩き)にする
		playerState = 2;
	}

	//xとzの移動速度がなかったら(スティックの入力がなかったら)
	else
	{
		//ステートを0(待機)にする
		playerState = 0;
	}
}

//アニメーションの再生
void Player::PlayAnimation()
{
	//switch文
	switch (playerState) {
		//プレイヤーステートが0(待機)だったら
	case 0:
		//待機アニメーションを再生する
		modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら
	case 1:
		//ジャンプアニメーションを再生する
		modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//プレイヤーステートが2(歩き)だったら
	case 2:
		//歩きアニメーションを再生する
		modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
		//プレイヤーステートが3(ダッシュ)だったら
	case 3:
		//ダッシュアニメーションを再生する
		modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

//描画処理
void Player::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する
	modelRender.Draw(rc);
	fontRender.Draw(rc);
}