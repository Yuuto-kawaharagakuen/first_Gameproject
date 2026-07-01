#pragma once
#include <time.h>
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
	static const int RANKING_MAX = 5;   //static→　このソースファイル（.cpp/.h）の中だけでしか見えない変数にする
	bool TryRegister(int score);     //ランクインしたらtrue
	int GetRank(int score) const;    //何位か（圏外は-1)
	const RankingEntry& Get(int index)const { return m_entries[index]; }      //index番目のランキングデータ(RankingEntry)を、コピーせず・書き換え不可の状態で外部に渡す  
	int GetCount() const { return m_count; }      //コピーするとのメモリと時間が毎回かかる。ランキング表示のたびにGetCount()の回数分（最大5回）コピーが走るのは無駄なので、& をつけて参照で返す　　　　　　&=コピーを作らず、元のデータそのものを指し示す
	                                                // 1つの値を返すだけなら → return      // 複数の値を同時に変更したいなら → &
private:                                                      //int a = 5;
	                                                           //int& ref = a;   
															   //ref = 99;     
	                                                           // refを変えると a も 99 になる
RankingEntry m_entries[RANKING_MAX] = {};
	int          m_count = 0;
};

//グローバルインスタンスの宣言
extern RankingManager g_rankingManager;      //externをつけることで宣言にし、定義は別のとこで1つだけ（RankingScene.cpp）、他のファイルはそれを参照する
                                             //externをつけないと,#includeするたびにRankingManager g_rankingManagerが作られてしまい、LNK2005(多重定義エラー)になる
// extern={この変数の宣言はここだけど,定義は別のファイルで行っている}と教える                                                    逆はLNK2001(未解決の外部シンボル[宣言はあるが定義がない])