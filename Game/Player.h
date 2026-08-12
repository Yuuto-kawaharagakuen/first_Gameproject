#pragma once

class Player :public IGameObject
{
public:
	Player();
	~Player();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();
	//ステート管理
	void ManageState();
	//アニメーションの再生
	void PlayAnimation();
	//フリーズスキル(Yボタン、30秒クールダウン)の更新
	void UpdateFreezeSkill();

	//メンバ変数
	FontRender fontRender;
	FontRender freezeFontRender; // フリーズスキルのクールダウン表示用
	ModelRender modelRender; //モデルレンダー
	Vector3 position;
	enum EnAnimatitonClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController characterController;
	Vector3 moveSpeed;
	Quaternion rotation;
	Vector3 facingDir = Vector3::AxisX;  

	int playerState = 0;
	int crystalCount = 0;
	int runnningState = 0;
	int jumpState;
	bool resetState;
	// ダッシュ(Bボタンで切り替え)
	bool isDashing = false;

	// クリスタルを一定時間止めるフリーズスキル
	bool isStopped = false;
	float stopTimer = 0.0f;
	float cooldownTimer = 0.0f;
};