// �Q�[���V�[���N���X�̃C���^�[�t�F�[�X
// ���|���o

#pragma once

// �w�b�_�C���N���[�h
#include "StepTimer.h"
#include "GameContext.h"
#include "Manager\GameSceneManager.h"

// �Q�[���V�[���N���X
class GameScene
{
public:
	// �R���X�g���N�^
	GameScene() = default;

public:
	// �f�X�g���N�^
	virtual ~GameScene() = default;

public:
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�揈��
	virtual void Render() = 0;
	// �I������
	virtual void Finalize() = 0;
};