// �v���C�V�[���̃\�[�X
#pragma once

#include "..\..\GameScene.h"
#include <Keyboard.h>

#include "..\..\Manager\GameObjectManager.h"
#include "..\..\GameObject\DebugCamera.h"
#include "..\..\GameObject\TargetCamera.h"
#include "..\..\GameObject\FixedCamera.h"
#include "..\..\GameObject\GridFloor.h"
#include "..\..\UI\Moji.h"

class PlayScene :
	public GameScene
{
public:
	enum State
	{
		STATE_DEMO,		// �f����
		STATE_PLAY,		// �v���C��(����\)
		STATE_CLEAR,	// �N���A
		STATE_DEAD,		// ���S

		SUM_STATE
	};

public:
	PlayScene();
	~PlayScene();
	
	// ���J����

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapedTime) override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;
	// �X�V����(�f����) 
	void StateDemo(float elapedTime);
	// �X�V����(�v���C��)
	void StatePlay(float elapedTime);
	// �X�V����(�N���A)
	void StateClear(float elasedTime);
	// �X�V����
	void StateDead(float elasedTime);

private:
	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera>			m_pDebugCamera;
	// �^�[�Q�b�g�J����
	std::unique_ptr<TargetCamera>			m_pTargetCamera;
	// �Œ�J����
	std::unique_ptr<FixedCamera>			m_pFixedCamera;
	// �O���b�h�t���A
	std::unique_ptr<GridFloor>				m_pGridFloor;
	// �L�[�{�[�h�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_pKeyboardTracker;
	// �t�F�[�h�A�E�g�̎���
	float									m_fadeTime;
	// �J�E���g
	int										m_count;
	// �f�o�b�O�J�����Ƃ̐؂�ւ�
	bool									m_debugCameraMode;
	// �f�o�b�O���[�h
	bool									m_debugMode;
	// �^�C���i�s�̐؂�ւ�
	bool									m_debugTimeMode;
	// �X�e�[�g�Ǘ�
	State									m_state;
	// �I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<GameObjectManager>		m_pGameObjectManager;
	// �^�C���p�̕���
	Moji									m_timeMoji;
	// �����̃e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureMoji;
	float									m_wait;

};

