// 点数を管理するマネージャー
#pragma once
class ScoreManager
{	
private:
	ScoreManager();
public:
	~ScoreManager();
// メンバ変数
public:
	// スコアを加算(加算する数）
	void AddScore(const int& vnum = 1);
	// スコアを返す
	int  GetScore() const;
	// スコアのリセット
	void ScoreReset();
	// タイムを減算(減算する数）
	void CountTime(const float& vnum = 1.0f);
	// タイムを返す
	float GetTime() const;
	// タイムのセッタ
	void SetTime(const float& vnum = 0.0f);
	// プレイヤーHPのセッタ
	void SetPlayerHP(const int& vnum = 1.0f);
	// プレイヤーHPのゲッタ
	int GetPlayerHP();
	// プレイヤーSPのセッタ
	void SetPlayerSP(const int& vnum = 1.0f);
	// プレイヤーSPのゲッタ
	int GetPlayerSP();
	// プレイヤーCPのセッタ
	void SetPlayerCP(const int& vnum = 1.0f);
	// プレイヤーCPのゲッタ
	int GetPlayerCP();
public:
	// オブジェクトへのポインタを返す
	static ScoreManager* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// オブジェクトを生成して、ポインタを格納
			m_pInstance.reset(new ScoreManager());
		}
		// オブジェクトへのポインタを返す
		return m_pInstance.get();
	}
private:
	static std::unique_ptr<ScoreManager> m_pInstance;

// メンバ変数
private:
	// ゲームの総合スコア
	int										m_score;
	// 時間
	float									m_time;
	// プレイヤーのHP
	int										m_playerHP;
	// プレイヤーのSP
	int										m_playerSP;
	// プレイヤーのCP
	int										m_playerCP;
};

