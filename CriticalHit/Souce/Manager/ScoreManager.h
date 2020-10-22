// �_�����Ǘ�����}�l�[�W���[
#pragma once
class ScoreManager
{	
private:
	ScoreManager();
public:
	~ScoreManager();
// �����o�ϐ�
public:
	// �X�R�A�����Z(���Z���鐔�j
	void AddScore(const int& vnum = 1);
	// �X�R�A��Ԃ�
	int  GetScore() const;
	// �X�R�A�̃��Z�b�g
	void ScoreReset();
	// �^�C�������Z(���Z���鐔�j
	void CountTime(const float& vnum = 1.0f);
	// �^�C����Ԃ�
	float GetTime() const;
	// �^�C���̃Z�b�^
	void SetTime(const float& vnum = 0.0f);
	// �v���C���[HP�̃Z�b�^
	void SetPlayerHP(const int& vnum = 1.0f);
	// �v���C���[HP�̃Q�b�^
	int GetPlayerHP();
	// �v���C���[SP�̃Z�b�^
	void SetPlayerSP(const int& vnum = 1.0f);
	// �v���C���[SP�̃Q�b�^
	int GetPlayerSP();
	// �v���C���[CP�̃Z�b�^
	void SetPlayerCP(const int& vnum = 1.0f);
	// �v���C���[CP�̃Q�b�^
	int GetPlayerCP();
public:
	// �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
	static ScoreManager* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// �I�u�W�F�N�g�𐶐����āA�|�C���^���i�[
			m_pInstance.reset(new ScoreManager());
		}
		// �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_pInstance.get();
	}
private:
	static std::unique_ptr<ScoreManager> m_pInstance;

// �����o�ϐ�
private:
	// �Q�[���̑����X�R�A
	int										m_score;
	// ����
	float									m_time;
	// �v���C���[��HP
	int										m_playerHP;
	// �v���C���[��SP
	int										m_playerSP;
	// �v���C���[��CP
	int										m_playerCP;
};

