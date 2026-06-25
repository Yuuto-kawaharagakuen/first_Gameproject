#pragma once

class Player:public IGameObject
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

	//メンバ変数
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


	int playerState = 0;
	int crystalCount = 0;
	int runnningState = 0;
	int jumpState;
	bool resetState;
};

