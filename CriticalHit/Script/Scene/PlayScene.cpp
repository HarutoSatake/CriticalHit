
#include "pch.h"
#pragma warning(disable: 4100)

#include <CommonStates.h>
#include <WICTextureLoader.h>
#include <string>

#include "PlayScene.h"
#include "Font.h"


#include "CollisionManager.h"
#include "ScoreManager.h"
#include "EffectManager.h"

#include "DeviceResources.h"
#include "View.h"
#include "Projection.h"

#include "Player.h"
#include "NormalEnemy.h"
#include "EnemyGenerator.h"
#include "PseudoObject.h"
#include "Reticule.h"
#include "SkyDoom.h"
#include "Ground.h"
#include "HPGauge.h"
#include "SpecialUI.h"
#include "ChargeUI.h"

#include "Adx2Le.h"
#include "Resources\Sound\Soundcue.h"

PlayScene::PlayScene()
	: m_state(STATE_DEMO)
	, m_fadeTime(0.0f)
	, m_wait(0.0f)
{
	m_count = 0;
	m_debugCameraMode = false;
	m_debugMode = false;
	m_debugTimeMode = false;

	ScoreManager::GetInstance()->ScoreReset();
}


PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	// BGM�Đ�
	GameContext<Adx2Le>::Get()->SetVolume(0.5f);
	GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_PLAY);
	
	// ����[�Ă���

	// �Q�[���I�u�W�F�N�g�}�l�[�W���[����
	m_pGameObjectManager = std::make_unique<GameObjectManager>();

	GameContext<GameObjectManager>::Register(m_pGameObjectManager);
	// �v���C���[����
	std::unique_ptr<Player> player = std::make_unique<Player>(DirectX::SimpleMath::Vector3(0.0f, 3.0f, 5.0f), 0.2f);
	//// �^����Q������
	//std::unique_ptr<PseudoObject> pseudoObj1 = std::make_unique<PseudoObject>(DirectX::SimpleMath::Vector3(3.0f, 0.0f, -5.0f), DirectX::SimpleMath::Vector3(2.0f, 0.0f, 20.0f));
	//std::unique_ptr<PseudoObject> pseudoObj2 = std::make_unique<PseudoObject>(DirectX::SimpleMath::Vector3(-3.0f, 0.0f, 5.0f), DirectX::SimpleMath::Vector3(-2.0f, 0.0f, 20.0f));
	// ���e�B�N��
	std::unique_ptr<Reticule> reticule = std::make_unique<Reticule>();
	// �G�l�~�[
	std::unique_ptr<EnemyGenerator> enemyGenelator = std::make_unique<EnemyGenerator>(4.0f);
	// �X�J�C�h�[��
	std::unique_ptr<SkyDoom> skyDoom = std::make_unique<SkyDoom>();
	// �n��
	std::unique_ptr<Ground> ground = std::make_unique<Ground>();
	// HP�Q�[�W
	std::unique_ptr<HPGauge> hpGauge = std::make_unique<HPGauge>();
	// �X�y�V�����Q�[�W
	std::unique_ptr<SpecialUI> spUI = std::make_unique<SpecialUI>();
	// �`���[�W�|�C���g
	std::unique_ptr<ChargeUI> cpUI = std::make_unique<ChargeUI>();

	DirectX::CommonStates* state = GameContext<DirectX::CommonStates>().Get();
	DX::DeviceResources*   deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();
	m_pGridFloor = std::make_unique<GridFloor>(device, deviceContext, state, 10.0f, 10);

	// �f�o�b�O���[�h
	DebugMode::GetInstance()->SetDebugMode(false);
	// �g���b�J�[�֌W
	m_pKeyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// �R���e�L�X�g�ɒǉ�
	//m_pGameObjectManager->Add(std::move(pseudoObj1));
	//m_pGameObjectManager->Add(std::move(pseudoObj2));
	m_pGameObjectManager->Add(std::move(enemyGenelator));
	m_pGameObjectManager->Add(std::move(skyDoom));
	m_pGameObjectManager->Add(std::move(ground));
	m_pGameObjectManager->Add(std::move(reticule));
	m_pGameObjectManager->Add(std::move(player));
	m_pGameObjectManager->Add(std::move(hpGauge));
	m_pGameObjectManager->Add(std::move(spUI));
	m_pGameObjectManager->Add(std::move(cpUI));

	// �J��������
	m_pDebugCamera = std::make_unique<DebugCamera>();
	m_pFixedCamera = std::make_unique<FixedCamera>();
	m_pTargetCamera = std::make_unique<TargetCamera>();

	// �X�R�A�ƃ^�C�������Z�b�g
	ScoreManager::GetInstance()->ScoreReset();
	ScoreManager::GetInstance()->SetTime(60.0f);

	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		deviceResources->GetD3DDevice(),
		L"Resources\\Textures\\Font.png",
		nullptr, m_textureMoji.GetAddressOf());
	// �^�C������������
	m_timeMoji.Initialize(m_textureMoji.Get(), 670, 30, "00", DirectX::Colors::Black);
	GameContext<EffectManager>::Get()->TimerReset();

	// �r���[���W���Z�o����
	DirectX::SimpleMath::Vector3 eye(0.0f, 3.0f, 15.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 3.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	// �Z�o
	std::unique_ptr<View> view = std::make_unique<View>();
	view->CreateLookAt(eye, target, up);

	// �Q�[���R���e�L�X�g�ɒǉ�
	GameContext<View>::Register(view);
}

void PlayScene::Update(float elapedTime)
{
	m_pGameObjectManager->Update(elapedTime);
	// �e�X�e�[�g���Ƃ̍X�V��������
	switch (m_state)
	{
	case PlayScene::STATE_DEMO:
		StateDemo(elapedTime);
		break;
	case PlayScene::STATE_PLAY:
		StatePlay(elapedTime);
		break;
	case PlayScene::STATE_CLEAR:
		StateClear(elapedTime);
		break;
	case PlayScene::STATE_DEAD:
		StateClear(elapedTime);
		break;
	default:
		assert("�v���C�V�[���ɂ���Ȗ��O�̃X�e�[�g�͑��݂��܂���B");
		break;
	}	
	std::string time_str = std::to_string((int)ScoreManager::GetInstance()->GetTime());
	m_timeMoji.SetStr(time_str.data());
}

void PlayScene::Render()
{
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		Font::GetInstance()->Print(L"PlayUI", 0, 0, L"�����̓v���C�V�[���ł��B");
		m_pGridFloor->draw(GameContext<DX::DeviceResources>::Get()->GetD3DDeviceContext(), GameContext<View>::Get()->GetMatrix(), GameContext<Projection>::Get()->GetMatrix());
	}
	else
	{
			/*int score = ScoreManager::GetInstance()->GetScore();
			float time = ScoreManager::GetInstance()->GetTime();
			Font::GetInstance()->Print(L"Time", 0, 60, L"�c�莞��:%f", time);
			Font::GetInstance()->Print(L"Score", 0, 120, L"���Đ��F%d��", score);	*/
	}
	
	m_pGameObjectManager->Render();
	if (m_state == STATE_DEMO)
	{
		GameContext<EffectManager>::Get()->Render(EffectManager::FADE_OUT);
	}
	if (m_state == STATE_CLEAR || m_state == STATE_DEAD)
	{
		GameContext<EffectManager>::Get()->Render(EffectManager::FADE_IN);
	}
	/*int score = ScoreManager::GetInstance()->GetScore();*/
	m_timeMoji.Draw();
}

void PlayScene::Finalize()
{
	GameContext<Adx2Le>::Get()->Stop();
	Font::GetInstance()->reset();
	m_pGameObjectManager->Crear();
}

void PlayScene::StateDemo(float elapedTime)
{
	m_pFixedCamera->Update();
	// �t�F�[�h�A�E�g
	if (m_fadeTime > 1.0f)
	{
		m_state = STATE_PLAY;
	}
	m_fadeTime += elapedTime;

	DirectX::SimpleMath::Vector3 camera = DirectX::SimpleMath::Vector3(5 * sin(0), 0, 5 * cos(0));
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt(m_pFixedCamera->getEyePosition(),
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::UnitY);
	Projection* proj = GameContext<Projection>::Get();
	GameContext<EffectManager>::Get()->SetRenderState(m_pFixedCamera->getEyePosition(), view, GameContext<Projection>::Get()->GetMatrix());
}

void PlayScene::StatePlay(float elapedTime)
{
	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_pKeyboardTracker->Update(keyState);
	// �J�����؂�ւ�
	if (m_pKeyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::F5))
	{
		m_debugCameraMode = !m_debugCameraMode;
	}
	// �^�C���i�s�ؑ�
	if (m_pKeyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::T))
	{
		m_debugTimeMode = !m_debugTimeMode;
	}
	// �f�o�b�O���[�h�ؑ�
	if (m_pKeyboardTracker->IsKeyPressed(DirectX::Keyboard::Keys::F3))
	{
		if (DebugMode::GetInstance()->GetDebugMode())
		{
			m_pGameObjectManager->ChangeDebugMode(false);
			Font::GetInstance()->reset();
			DebugMode::GetInstance()->SetDebugMode(false);
		}
		else
		{
			m_pGameObjectManager->ChangeDebugMode(true);
			DebugMode::GetInstance()->SetDebugMode(true);
		}
	}

	// �J�����؂�ւ�����
	// �f�o�b�O�J����
	if (m_debugCameraMode)
	{
		m_pDebugCamera->update();
	}
	else
	{
		// �v���C���[�̍��W���擾
		std::vector<GameObject*> player = m_pGameObjectManager->Find("Player");
		if (!player.empty())
		{
			// �Œ�J����
			m_pFixedCamera->Update(player.front());
		}
	}
	float time = 0.0f;
	// �^�C���i�s����
	if (!m_debugTimeMode)
	{
		if (m_count >= 60)
		{
			// �^�C���X�V
			ScoreManager::GetInstance()->CountTime();
			m_count = 0;
		}
		m_count++;
	}
	time = ScoreManager::GetInstance()->GetTime();
	// ���U���g�V�[���J�ڃ`�F�b�N
	if (time <= 0.0f)
	{
		GameContext<EffectManager>::Get()->TimerReset();
		m_state = STATE_CLEAR;
	}
	int hp = ScoreManager::GetInstance()->GetPlayerHP();
	if (hp <= 0)
	{
		GameContext<EffectManager>::Get()->TimerReset();
		m_state = STATE_DEAD;
	}
}

void PlayScene::StateClear(float elapedTime)
{
	if (m_wait > 1.0f)
	{
		GameContext<GameSceneManager>::Get()->RequestScene("Result");
	}
	m_wait += elapedTime;
}

void PlayScene::StateDead(float elapedTime)
{
	if (m_wait > 1.0f)
	{
		GameContext<GameSceneManager>::Get()->RequestScene("Result");
	}
	m_wait += elapedTime;
}
