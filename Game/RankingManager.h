#pragma once
#include<ctime>
static const int RANKING_MAX = 5;

struct RankingEntry
{
	int score;
	time_t date;
	bool isNew;
};
class RankingManager
{
public:
	/*void Load(const wchar_t* filePath);
	void Save(const wchar_t* filePath);*/
	bool TryRegister(int score);     //ランクインしたらtrue
	int GetRank(int score) const;    //何位か（圏外は-1)
	const RankingEntry& Get(int index)const { return m_entries[index]; }
	int GetCount() const { return m_count; }

private:
	RankingEntry m_entries[RANKING_MAX] = {};
	int          m_count = 0;
};

//グローバルインスタンスの宣言
extern RankingManager g_rankingManager;
