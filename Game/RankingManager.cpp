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
		if (score > m_entries[i].score)return i;
	}
	if (m_count < RANKING_MAX)return m_count;
	return-1;
}

bool RankingManager::TryRegister(int score) {
	for (int i = 0;i < m_count;i++) //先にリセットすることで圏外の時に前回表示したところにNewが出るのを防ぐ
		m_entries[i].isNew = false;

	int rank = GetRank(score);
	if (rank < 0)return false;

	int insertPos = min(rank, RANKING_MAX - 1);
	for (int i = RANKING_MAX - 1;i > insertPos;i--)
		m_entries[i] = m_entries[i - 1];

	m_entries[insertPos].score = score;
	m_entries[insertPos].date = time(nullptr);
	m_entries[insertPos].isNew = true;

	m_count = min(m_count + 1, RANKING_MAX);
	return true;
}