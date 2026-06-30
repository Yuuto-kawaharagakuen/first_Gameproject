#pragma once
#include <time.h>
static const int RANKING_MAX = 5;   //static→　このソースファイル（.cpp/.h）の中だけでしか見えない変数にする

struct RankingEntry        //struct→複数のデータをひとまとめにして、1つの新しい型を作る　今回ではint,bool,dateをまとめる
{                          //class→データ＋それを操作する関数（メソッド）を持つもの　struct→複数の変数をまとめるだけ
	int score;
	time_t date;           //1970年1月1日からの経過秒数
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
