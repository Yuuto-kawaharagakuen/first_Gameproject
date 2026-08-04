#pragma once

//ばねカメラを使用したい場合は、SpringCameraをインクルードする。
#include "camera/SpringCamera.h"

class Player;
//ゲームカメラを制御する
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	SpringCamera m_springCamera;	//地形とのあたり判定込みのカメラ
	Player* m_player;
	Vector3 m_toCameraPos;
};

