#include "stdafx.h"
#include "RankingManager.h"
//#include<fstream>

//void RankingManager::Load(const wchar_t* filePath) {
//	std::ifstream ifs(filePath, std::ios::binary);
//	if (!ifs)return;
//	ifs.read((char*)&m_count, sizeof(m_count));
//	for (int i = 0;i < m_count;i++) {
//		ifs.read((char*)&m_entries[i].score, sizeof(int));
//		ifs.read((char*)&m_entries[i].date, sizeof(time_t));
//		m_entries[i].isNew = false;
//	}
//}

//void RankingManager::Save(const wchar_t* filePath) {
//	std::ofstream ofs(filePath, std::ios::binary);
//	ofs.write((char*)&m_count, sizeof(m_count));
//	for (int i = 0;i < m_count;i++) {
//		ofs.write((char*)&m_entries[i].score, sizeof(int));
//		ofs.write((char*)&m_entries[i].date, sizeof(time_t));
//	}
//}

int RankingManager::GetRank(int score)const {
	for (int i = 0;i < m_count;i++) {
		if (score > m_entries[i].score)return i;    // 何位かを返す（0〜4）0が1位,4が5位
	}
	if (m_count < RANKING_MAX)return m_count;       //m_countの中に入っている値（例えば3）を呼び出し元に返す  returnはコピーするから、m_countの値は変わらない
	return-1;            //「-1を返す」ことで下にあるif (rank < 0)return false;で終了できる
}

bool RankingManager::TryRegister(int score) {
	for (int i = 0;i < m_count;i++) //先にリセットすることで圏外の時に前回表示したところにNewが出るのを防ぐ
		m_entries[i].isNew = false; //この2文が下の2文より下だと,スコアが圏外の時に前回表示したところにNewが残ってしまう

	int rank = GetRank(score);
	if (rank < 0)return false;     // ← 圏外なら、ここで即終了して false を返す

	// ランクインした場合の処理（圏外のときはここに来ない）
	int insertPos = min(rank, RANKING_MAX - 1);
	for (int i = RANKING_MAX - 1;i > insertPos;i--)
		m_entries[i] = m_entries[i - 1];

	m_entries[insertPos].score = score;
	m_entries[insertPos].date = time(nullptr);    //引数は使わない、戻り値だけ使う
	m_entries[insertPos].isNew = true;

	m_count = min(m_count + 1, RANKING_MAX);
	return true;                             // RankingScene.cpp の SetScore の中のm_isRankedInにtrueかfalseがかえる
}                                            //falseを返した場合   NEW! は表示されない 下部に「今回のスコア : ◯◯点」が表示される
                                             //true を返した場合 　NEW!が表示される　　下部の「今回のスコア」は表示されない
