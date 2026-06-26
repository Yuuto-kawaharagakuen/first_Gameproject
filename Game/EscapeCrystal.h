#pragma once

class Player;

class EscapeCrystal:public IGameObject
{
public:
	EscapeCrystal();
	~EscapeCrystal();
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

	// Xキーで一度だけ5秒間動きを止めるためのフラグ/タイマー
	bool isStopped;
	bool stopUsed;
	float stopTimer;
	bool prevXDown;
};

