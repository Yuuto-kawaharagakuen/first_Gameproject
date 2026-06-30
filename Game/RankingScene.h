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
	bool           m_isRankedIn = false; //ランクインしたか

	FontRender     m_titleRender;
	FontRender     m_rankingRender[RANKING_MAX];
	FontRender     m_newLabelRender[RANKING_MAX]; //New用
	FontRender     m_currentScoreRender; //圏外時のみ
};

