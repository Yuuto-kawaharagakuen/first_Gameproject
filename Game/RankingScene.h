#pragma once
#include"RankingManager.h"
class RankingScene:public IGameObject
{
public:
	RankingScene();
	~RankingScene();
	void Update();
	void Render(RenderContext& rc);
	void SetScore(int s);

private:
	/*RankingManager m_ranking;*/
	int            m_currentScore = 0;
	bool           m_isRankedIn = false; //ランクインしたか していないか

	FontRender     m_titleRender;  //「ランキング」s
	FontRender     m_rankingRender[RankingManager::RANKING_MAX];  //順位と点数を表示するRender
	FontRender     m_newLabelRender[RankingManager::RANKING_MAX]; //New用
	FontRender     m_currentScoreRender; //圏外時のみ
};

