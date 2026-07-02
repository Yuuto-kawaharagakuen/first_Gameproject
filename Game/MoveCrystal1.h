#pragma once

class Player;

class MoveCrystal1 :public IGameObject
{
public:
	MoveCrystal1();
	~MoveCrystal1();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();

	//メンバ変数
	ModelRender modelRender;
	Vector3 position;
	int moveCount;
	Vector3 firstPosition;
	Quaternion rotation;	//クォータニオン。
	Player* player;		//プレイヤー。
	FontRender fontRender; //フォントレンダーを使用

	// Yボタンで一度だけ3秒間動きを止めるためのフラグ/タイマー
	// 使用後は30秒のクールダウンが入る
	bool isStopped;
	float cooldownTimer;
	float stopTimer; // 停止残り時間(秒)
	bool prevXDown;
};

