// �f�o�b�O���[�h����N���X�̃w�b�_
// ���|���o

#pragma once
class DebugMode
{
private:
	bool m_mode;
private:
	DebugMode();
public:
	~DebugMode();
	// �f�o�b�O���[�h�̃Z�b�^
	void SetDebugMode(bool v);
	// �f�o�b�O���[�h�̃Q�b�^
	bool GetDebugMode();
public:
	static DebugMode* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// �I�u�W�F�N�g�𐶐����āA�|�C���^���i�[
			m_pInstance.reset(new DebugMode());
		}

		// �I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_pInstance.get();
	}
private:
	static std::unique_ptr<DebugMode> m_pInstance;
};

