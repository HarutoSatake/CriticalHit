#include "pch.h"
#include "EnemyGenerator.h"
#include "GameContext.h"
#include "GameObjectManager.h"
#include "ScoreManager.h"
#include "Font.h"
#include "Utilities.h"

#include "NormalEnemy.h"
#include "SideMoveEnemy.h"
#include "WaveMoveEnemy.h"


EnemyGenerator::EnemyGenerator(float interval)
	: GameObject("EnemyGenerator")
	, m_interval(interval)
	, m_elapsedTime(0.0f)
	, m_lastScore(0)
{
	m_enemyList = EnemyList::NORMAL;
	// �^�C�����C����ǂݎ��

	// �z��Ɋi�[
}

EnemyGenerator::~EnemyGenerator()
{
}

void EnemyGenerator::Update(float elapsedTime)
{
	// ���݂̃X�R�A���擾
	int score = ScoreManager::GetInstance()->GetScore();
	if (m_lastScore - score == -3)
	{
		m_interval -= 1.0f;
		if (m_interval <= 1.0f)
		{
			m_interval = 1.0f;
		}
		m_lastScore = score;
	}
	m_elapsedTime += elapsedTime;
	std::vector<GameObject*> result = GameContext<GameObjectManager>::Get()->Find("Enemy");
	if (m_elapsedTime > m_interval)
	{
		for (int i = 0; i < static_cast<int>(result.size()); i++)
		{
			if (result[i]->GetPosition().z >= 15.0f)
			{
				result[i]->Destroy(result[i]);
			}
		}
		
		if (static_cast<int>(result.size()) < 3)
		{
			Generate();
			m_elapsedTime = 0.0f;
		}
	}
	/*Font::GetInstance()->Print(L"EnemySUM", 0.0f, 210.0f, L"�G�����F%d", result.size());*/
	// �X�R�A�}�l�[�W���[����^�C�����擾
	/*int time = static_cast<int>(ScoreManager::GetInstance()->GetTime());*/
	// �^�C���ɑ΂���G�𐶐�



}

void EnemyGenerator::Render()
{
}

void EnemyGenerator::Generate() const
{
	// std::unique_ptr<NormalEnemy> enemy = std::make_unique<NormalEnemy>(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// �G�l�~�[�̎�ނ̗�������
	int ran = RandomInt(0, EnemyList::SUM - 1);
	// ���W�̗�������
	DirectX::SimpleMath::Vector3 pos = RandomVector(DirectX::SimpleMath::Vector3(-3.0f, 0.0f, 0.0f), DirectX::SimpleMath::Vector3(3.0f, 3.0f, 0.0f));
	pos.z = -10.0f;
	
	switch (ran)
	{
	case EnemyList::NORMAL:
	{
		std::unique_ptr<NormalEnemy> normal = std::make_unique<NormalEnemy>(pos);
		GameContext<GameObjectManager>::Get()->Add(std::move(normal));
		break;
	}
	case EnemyList::SIDE:
	{
		std::unique_ptr<SideMoveEnemy> side = std::make_unique<SideMoveEnemy>(pos);
		GameContext<GameObjectManager>::Get()->Add(std::move(side));
		break;
	}
	case EnemyList::WAVE:
	{
		std::unique_ptr<WaveMoveEnemy> wave = std::make_unique<WaveMoveEnemy>(pos);
		GameContext<GameObjectManager>::Get()->Add(std::move(wave));
		break;
	}
	default:
		assert("EnemyList�̒l���s���ł��B");
		break;
	}
	
	
}

void EnemyGenerator::OnCollision(GameObject * object)
{
	// �s�g�p
	(void)object;
}
