#include "pch.h"
#include "ScoreManager.h"

std::unique_ptr<ScoreManager> ScoreManager::m_pInstance = nullptr;

ScoreManager::ScoreManager()
{
	m_score = 0;
	m_playerHP = 0;
}


ScoreManager::~ScoreManager()
{

}

void ScoreManager::AddScore(const int& vnum)
{
	m_score += vnum;
}

int ScoreManager::GetScore() const	
{
	return m_score;
}

void ScoreManager::ScoreReset()
{
	m_score = 0;
}

void ScoreManager::CountTime(const float & vnum)
{
	m_time -= vnum;
}

float ScoreManager::GetTime() const
{
	return m_time;
}

void ScoreManager::SetTime(const float& vnum)
{
	m_time = vnum;
}

void ScoreManager::SetPlayerHP(const int & vnum)
{
	m_playerHP = vnum;
}

int ScoreManager::GetPlayerHP()
{
	return m_playerHP;
}

void ScoreManager::SetPlayerSP(const int & vnum)
{
	m_playerSP = vnum;
}

int ScoreManager::GetPlayerSP()
{
	return m_playerSP;
}

void ScoreManager::SetPlayerCP(const int & vnum)
{
	m_playerCP = vnum;
}

int ScoreManager::GetPlayerCP()
{
	return m_playerCP;
}
