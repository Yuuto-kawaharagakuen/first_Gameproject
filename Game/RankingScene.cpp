#include "stdafx.h"
#include "RankingScene.h"
#include"Title.h"
#include"RankingManager.h"

RankingManager g_rankingManager;

RankingScene::RankingScene() {
	m_titleRender.SetPosition({ -300.0f,400.0f,0.0f });
	m_titleRender.SetColor(g_vec4Black);
	m_titleRender.SetScale(2.5f);
	m_titleRender.SetText(L"ランキング");

	for (int i = 0;i < RANKING_MAX;i++) {
		m_rankingRender[i].SetPosition({ -300.0f,250.0f - i * 100.0f,0.0f });
		m_rankingRender[i].SetColor(g_vec4Black);
		m_rankingRender[i].SetScale(1.8f);

		//Newラベル
		m_newLabelRender[i].SetPosition({ -500.0f,250.0f - i * 100.0f,0.0f });
		m_newLabelRender[i].SetColor(g_vec4Yellow);
		m_newLabelRender[i].SetScale(1.8f);
		m_newLabelRender[i].SetText(L""); //最初は空
	}

	m_currentScoreRender.SetPosition({ -400.0f,-300.0f,0.0f });
	m_currentScoreRender.SetColor(g_vec4Black);
	m_currentScoreRender.SetScale(1.8f);
}

RankingScene::~RankingScene(){}

void RankingScene::SetScore(int s) {
	m_currentScore = s;
	/*m_ranking.Load(L"Assets/ranking.dat");*/
	m_isRankedIn = g_rankingManager.TryRegister(m_currentScore); //グローバル
	/*m_ranking.Save(L"Assets/ranking.dat");*/
}

void RankingScene::Update() {
	//ランキング更新処理
	for (int i = 0;i < g_rankingManager.GetCount();i++) {
		const auto& entry = g_rankingManager.Get(i);

		wchar_t buf[64];
		//ランクインした行にNew!をつける
		swprintf_s(buf, L"%d位  %d点", i + 1, entry.score);
        m_rankingRender[i].SetText(buf);

		//NEW
		if (entry.isNew) {
			m_newLabelRender[i].SetText(L"NEW!");
		}
		else {
			m_newLabelRender[i].SetText(L"");
		}
	}

	//圏外なら下部に今回のスコアを表示
	if (!m_isRankedIn) {
		wchar_t scoreBuf[64];
		swprintf_s(scoreBuf, L"今回のスコア:%d点", m_currentScore);
		m_currentScoreRender.SetText(scoreBuf);
	}

	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void RankingScene::Render(RenderContext& rc) {
	m_titleRender.Draw(rc);
	for (int i = 0;i < g_rankingManager.GetCount();i++) {
		m_newLabelRender[i].Draw(rc);
		m_rankingRender[i].Draw(rc);
	}
	//圏外の時のみ描画
	if (!m_isRankedIn) {
		m_currentScoreRender.Draw(rc);
	}
}