// �Q�[���R���e�L�X�g(�o�^���ꂽ��̃N���X��ǂݍ��ނ��Ƃ̂ł���N���X)
// ���|���o

#pragma once

// �w�b�_�C���N���[�h
#include <cassert>
#include <memory>

template<typename Context>
// �Q�[���R���e�L�X�g�N���X
class GameContext final
{
private:
	// �o�^���ꂽ�R���e�L�X�g
	static Context* s_context;

public:
	// �R���e�L�X�g��o�^����
	static void Register(const std::unique_ptr<Context>& context)
	{
		s_context = context.get();
	}

	// �R���e�L�X�g���擾����
	static Context* Get()
	{
		assert(s_context && "�s���ȃR���e�L�X�g�ł��B");

			return s_context;
	}
};

template<typename Context>
Context* GameContext<Context>::s_context = nullptr;