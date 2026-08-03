#pragma once

class Player;

class Crystal :public IGameObject
{
public:
	Crystal();
	~Crystal();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//回転処理
	void Rotation();

	//メンバ変数
	ModelRender modelRender;
	Vector3 position;
	int moveCount;
	Vector3 firstPosition;
	Quaternion rotation;	//クォータニオン。
	Player* player;		//プレイヤー。
};