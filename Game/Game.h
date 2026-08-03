#pragma once
#include"sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class Crystal;
class Goal;
class GoalUI;
class CountUI;
class MoveCrystal1;
class EscapeCrystal;
//Gameシーンを管理するクラス
class Game : public IGameObject
{
public:
	Game();
	~Game();
	//更新処理
	void Update();
	Player* player;
	GameCamera* gameCamera;
	BackGround* backGround;
	SoundSource* gameBGM;
	Crystal* crystal;
	CountUI* countUI;
	Goal* goal;
	GoalUI* goalUI;
	float goalUIElapsedTime;
	SkyCube* sky;
	MoveCrystal1* moveCrystal1;
	EscapeCrystal* escapeCrystal;
};

