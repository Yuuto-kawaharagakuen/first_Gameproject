#pragma once

class Player;
//ゲームカメラを制御する
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_player;
	Vector3 m_toCameraPos;
};

