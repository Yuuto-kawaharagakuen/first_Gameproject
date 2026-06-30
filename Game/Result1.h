#pragma once
#include"RankingScene.h"
//#include"sound/SoundEngine.h"
//ゲームクリア
class Result1:public IGameObject
{
public:
	Result1();
	~Result1();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//メンバ変数
	SpriteRender spriteRender;
	FontRender fontRender;
	SoundSource* ResultBGM;
	// スコア表示用フォントと値
	FontRender scoreRender;
	int score = 0;
	float elapsedTime = 0.0f;

	void SetElapsedTime(float time) { elapsedTime = time; }
	void SetScore(int s) { score = s; }
};

