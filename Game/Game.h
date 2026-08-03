#pragma once
#include"sound/SoundSource.h"
#include <random>


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
	void Render(RenderContext& rc);
	void UpdatePauseMenu();
	void DrawPauseMenu(RenderContext& rc);
	void EnterPause();
	void ExitPause(bool backToTitle);

	bool m_isPaused = false;
	int m_pauseCursor = 0;   //0=続ける 1=タイトルへ
	bool m_gameActiveBeforePause = true;

	SpriteRender m_pauseOverlaySprite; //画面全体を暗くする半透明パネル
	SpriteRender m_pausePanelSprite; //中央のパネル

	FontRender m_pauseTitleText; //ポーズ
	FontRender m_pauseCursorText; //「▶」
	FontRender m_pauseOption1Text; //つづける
	FontRender m_pauseOption2Text; //タイトルへ
	 
	//つづける、タイトルへ それぞれのカーソル位置
	float m_pauseCursorX = -250.0f;
	float m_pauseCursorPosOption1Y = 50.0f;
	float m_pauseCursorPosOption2Y = -50.0f;

	Player* player;
	GameCamera* gameCamera;
	BackGround* backGround;
	SoundSource* gameBGM;
	SpriteRender spriteRender;
	Crystal* crystal;
	Crystal* crystal4;
	CountUI* countUI;
	Goal* goal;
	GoalUI* goalUI;
	float goalUIElapsedTime;
	SkyCube* sky;
	MoveCrystal1* moveCrystal1;
	EscapeCrystal* escapeCrystal;

	std::mt19937& GetRandomEngine()
	{
		static std::mt19937 engine(std::random_device{}());
		return engine;
	}

	float GetRandomValue(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(GetRandomEngine());
	}
};

