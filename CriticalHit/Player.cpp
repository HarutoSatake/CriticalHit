#include "pch.h"
#pragma warning(disable: 4100)
#include "Player.h"
#include "Bullet.h"
#include "ChargeShot.h"

#include <memory>
#include <math.h>
#include <vector>
#include <Keyboard.h>
#include <Mouse.h>
#include <Effects.h>
#include <VertexTypes.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "GameSceneManager.h"
#include "ScoreManager.h"
#include "View.h"
#include "Font.h"
#include "Reticule.h"

#include "Adx2Le.h"
#include "Resources\Sound\Soundcue.h"

Player::Player(const DirectX::SimpleMath::Vector3& position, float fireInterval)
	: GameObject("Player")
	, m_fireInterval(fireInterval)
	, m_elapsedTime(0.0f)
	, m_isLoading(false)
	, m_horizontalAngle(-180.0f)
	, m_pGeometricPrimitive()
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_shotPower(0.0f)
	, m_chargeInterval(0)
	, m_laserPoint(0)
	, m_laserCount(0)
	, m_lastScore(0)
	, m_hp(MAX_HP)
	, m_state(STATE::NORMAL_STATE)

{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	
	m_scale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 1.0f);
	m_position = position;
	m_collider = std::make_unique<BoxCollider>(this, m_scale);
	m_rotation = DirectX::SimpleMath::Vector3(0.0f, 180.0f, 0.0f);

	m_pMouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	m_colFlag = false;
	m_pGeometricPrimitive = DirectX::GeometricPrimitive::CreateBox(deviceContext, m_scale);
	// ���f���`�揀��
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(deviceResources->GetD3DDevice());

	factory->SetDirectory(L"Resources/Models");

	m_pModel = DirectX::Model::CreateFromCMO(
		deviceResources->GetD3DDevice(),
		L"Resources/Models/aircraft.cmo",
		*factory);

	delete factory;
	// �X�R�A�}�l�[�W���[�ɏ���HP��o�^
	// �X�R�A�}�l�[�W���[�V���O���g���͂Ȃ񂩖��ʂȂ̂ŉ��ǂ̓R���e�L�X�g�ǉ��ł��肢���܂�
	ScoreManager::GetInstance()->SetPlayerHP(m_hp);
	ScoreManager::GetInstance()->SetPlayerSP(m_laserPoint);
	ScoreManager::GetInstance()->SetPlayerCP(m_shotPower);
}

Player::~Player()
{

}

void Player::Update(float elapsedTime)
{
	DirectX::Keyboard::KeyboardStateTracker* key = GameContext<DirectX::Keyboard::KeyboardStateTracker>::Get();
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	m_pMouseTracker->Update(mouseState);

	// ���x�͖��񏉊���
	m_velocity = DirectX::SimpleMath::Vector3::Zero;
	
	if (m_state != STATE::SPECIAL_STATE)
	{
		int score = ScoreManager::GetInstance()->GetScore();
		m_laserPoint = (score - m_lastScore);

		// ���
		if (m_laserPoint > 5)
		{
			m_laserPoint = 5;
		}
	}
	switch (m_state)
	{
	case Player::DEMO_STATE:
		DemoState(elapsedTime);
		break;
	case Player::NORMAL_STATE:
		NormalState(elapsedTime);
		break;
	case Player::CHARGE_STATE:
		ChargeState(elapsedTime);
		break;
	case Player::SPECIAL_STATE:
		SpecioalState(elapsedTime);
		break;
	case Player::DESTROY_STATE:
		DestroyState(elapsedTime);
		break;
	case Player::CLEAR_STATE:
		ClearState(elapsedTime);
		break;
	default:
		break;
	}
	// �f�o�b�O���[�h��
	if (DebugMode::GetInstance()->GetDebugMode())
	{
		if (key->IsKeyPressed(DirectX::Keyboard::C))
		{
			ScoreManager::GetInstance()->AddScore(5);
		}
		// �����蔻��X�V
		DirectX::SimpleMath::Vector3 ColPos = m_collider->GetPosition();
		DirectX::SimpleMath::Vector3 ColOffSet = m_collider->GetOffset();
		// �e�ۏ��
		/*Font::GetInstance()->Print(L"PlayerColPos", 0, 120, L"�v���C���[���W�F%f,%f,%f", ColPos.x, ColPos.y, ColPos.z);
		Font::GetInstance()->Print(L"PlayerColOff", 0, 150, L"�v���C���[�T�C�Y�F%f,%f,%f", ColOffSet.x, ColOffSet.y, ColOffSet.z); */
	}
	else
	{
		//// �K�v��񕶎��o��
		//Font::GetInstance()->Print(L"HP", 0, 0, L"�v���C���[HP�F%d", m_hp);
		//Font::GetInstance()->Print(L"Charge", 0, 150, L"�`���[�W�F%f", m_shotPower);
		//Font::GetInstance()->Print(L"Laser", 0, 180, L"���˃Q�[�W�F%d", m_laserPoint);
	}
	m_position += m_velocity;

	GameContext<CollisionManager>::Get()->add(m_collider.get());
	ScoreManager::GetInstance()->SetPlayerSP(m_laserPoint);
	ScoreManager::GetInstance()->SetPlayerCP(m_shotPower);
}



void Player::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotation.x));
	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians( m_rotation.y));
	world *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation.z));
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// ���f���`��
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	Projection* proj = GameContext<Projection>().Get();
	View* view = GameContext<View>().Get();
	DirectX::CommonStates* states = GameContext<DirectX::CommonStates>().Get();
	/*DirectX::BasicEffect* effects = GameContext<DirectX::BasicEffect>().Get();*/

	// ���f���`��ɂ̓R�����X�e�[�g�����I
	m_pModel->Draw(deviceContext, *states, world, view->GetMatrix(), proj->GetMatrix());
	if (m_debugMode)
	{
		// �����蔻��̉���
		world = DirectX::SimpleMath::Matrix::Identity;
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_collider->GetPosition());

		m_pGeometricPrimitive->Draw(world, view->GetMatrix(), proj->GetMatrix(), DirectX::Colors::Red, nullptr, true);
	}
}

void Player::OnCollision(GameObject * object)
{
	if (m_state != STATE::DESTROY_STATE)
	{
		if (object->GetTag() == "EnemyBullet")
		{
			// �_���[�W�T�E���h
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_HIT);
			// HP�����Z
			m_hp--;
			// �X�R�A�}�l�[�W���[���X�V
			ScoreManager::GetInstance()->SetPlayerHP(m_hp);
			Destroy(object);
		}
	}
}
// �X�V����(�f���̎�
void Player::DemoState(float elapsedTime)
{
}
// �X�V����(��{�̎�
void Player::NormalState(float elapsedTime)
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	Move(elapsedTime);

	if (m_isLoading)
	{
		m_elapsedTime += elapsedTime;

		if (m_elapsedTime > m_fireInterval)
		{
			m_isLoading = false;
		}
	}
	// �e������
	if (!m_isLoading)
	{
		// �ʏ�e
		if (m_pMouseTracker->leftButton == m_pMouseTracker->HELD)
		{
			Shot(0);
		}
		// �`���[�W�e(�ʏ�e�Ɠ����ɔ��˂ł��Ȃ��悤��
		else if(m_pMouseTracker->rightButton == m_pMouseTracker->HELD)
		{	
			m_state = STATE::CHARGE_STATE;
		}
		// ���[�U�[
		if (m_pMouseTracker->middleButton == m_pMouseTracker->PRESSED && m_laserPoint >= 5)
		{
			GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_SPECIAL);
			m_state = STATE::SPECIAL_STATE;
		}
	}
	
	if (m_hp <= 0)
	{
		GameContext<Adx2Le>::Get()->Play(CRI_SOUNDCUE_EXPLOSION);
		m_hp = 0;
		m_state = STATE::DESTROY_STATE;
	}
}
// �X�V����(�`���[�W���̎�
void Player::ChargeState(float elapsedtime)
{
	Move(elapsedtime);
	if (m_pMouseTracker->rightButton == m_pMouseTracker->HELD)
	{
		if (m_chargeInterval >= 8)
		{
			m_shotPower += 1.0f;
			if (m_shotPower > 5.0f)
				m_shotPower = 5.0f;
			m_chargeInterval = 0;
		}
		else
		{
			m_chargeInterval++;
		}
		
	}
	if (m_pMouseTracker->rightButton == m_pMouseTracker->RELEASED)
	{
		// �{�^�����痣���ꂽ��`���[�W�����e�𔭎�
		Shot(1);
		m_shotPower = 0.0f;
		m_chargeInterval = 0;
		m_state = STATE::NORMAL_STATE;
	}
}
// �X�V����(�X�y�V�����������̎�
void Player::SpecioalState(float elapsedTime)
{
	Move(elapsedTime);
	m_elapsedTime += elapsedTime;
	if (m_elapsedTime > m_fireInterval - 0.1f)
	{
		Shot();
	}
	m_laserCount++;
	if (m_laserCount > 120)
	{
		m_laserPoint--;
		m_laserCount = 0;
		if (m_laserPoint == 0)
		{
			m_lastScore = ScoreManager::GetInstance()->GetScore();
			m_state = STATE::NORMAL_STATE;
		}
	}
}
// �X�V����(�j�󂳂ꂽ��
void Player::DestroyState(float elapsedTime)
{
	// ���Ďp��
	m_velocity.y = -0.05f;
	m_rotation.x = 20.0f;
	m_rotation.z += 2.0f;

}
// �X�V����(�N���A������
void Player::ClearState(float elapsedTime)
{
}
// �ړ�����
void Player::Move(float elapsedtime)
{
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	// ��_�����x,y�e�X�̋��������߂�
	DirectX::SimpleMath::Vector2 base_length;
	base_length.x = std::abs(m_position.x - BASE_VEC.x);
	base_length.y = std::abs(m_position.y - BASE_VEC.y);
	// WASD�ړ�
	// �㉺�ړ�
	if (key.IsKeyDown(DirectX::Keyboard::W))
	{
		m_velocity.y = MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE)
			m_velocity.y /= 2;
		m_rotation.x -= 2.0f;
		// �ړ��ʐ�������
		if (base_length.y > 4.0f && BASE_VEC.y <= m_position.y)
			m_velocity.y = 0.0f;
	}
	else if (key.IsKeyDown(DirectX::Keyboard::S))
	{
		m_velocity.y = -MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE) m_velocity.y /= 2;
		m_rotation.x += 2.0f;
		// �ړ��ʐ�������
		if (base_length.y > 4.0f && BASE_VEC.y > m_position.y)
			m_velocity.y = 0.0f;
	}
	else
	{
		// �������p�x�����Ƃɖ߂�
		if (m_rotation.x > 0)
		{
			m_rotation.x -= 2.0f;

		}
		else if (m_rotation.x < 0)
		{
			m_rotation.x += 2.0f;
		}
		else
		{
			m_rotation.x = 0.0f;

		}

	}
	// ���E�ړ�
	if (key.IsKeyDown(DirectX::Keyboard::A))
	{
		m_velocity.x = -MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE) m_velocity.x /= 2;
		m_rotation.z += 3.0f;
		m_rotation.y += 2.0f;
		// �ړ��ʐ�������
		if (base_length.x > 5.0f && BASE_VEC.x >= m_position.x)
			m_velocity.x = 0.0f;

	}
	else if (key.IsKeyDown(DirectX::Keyboard::D))
	{
		m_velocity.x = MOVE_SPEED;
		if (m_state == STATE::CHARGE_STATE) m_velocity.x /= 2;
		m_rotation.z -= 3.0f;
		m_rotation.y -= 2.0f;
		// �ړ��ʐ�������
		if (base_length.x > 5.0f && BASE_VEC.x <= m_position.x)
			m_velocity.x = 0.0f;
	}
	else
	{
		// �������p�x�����Ƃɖ߂�
		if (m_rotation.z > 0)
		{
			m_rotation.z -= 1.0f;
		}
		else if (m_rotation.z < 0)
		{
			m_rotation.z += 1.0f;
		}
		else
		{
			m_rotation.z = 0.0f;
		}
		// �������p�x�����Ƃɖ߂�
		if (m_rotation.y > 180)
		{
			m_rotation.y -= 1.0f;
		}
		else if (m_rotation.y < 180)
		{
			m_rotation.y += 1.0f;
		}
		else
		{
			m_rotation.y = 180.0f;
		}
	}

	// ��]�̒���
	// X��
	if (m_rotation.x > 30.0f)
	{
		m_rotation.x = 30.0f;
	}
	else if (m_rotation.x < -30.0f)
	{
		m_rotation.x = -30.0f;
	}
	// Y��
	if (m_rotation.y > 200.0f)
	{
		m_rotation.y = 200.0f;
	}
	else if (m_rotation.y < 160.0f)
	{
		m_rotation.y = 160.0f;
	}

	// Z��
	if (m_rotation.z > 20.0f)
	{
		m_rotation.z = 20.0f;
	}
	else if (m_rotation.z < -20.0f)
	{
		m_rotation.z = -20.0f;
	}
}
// �e�۔��ˏ���
void Player::Shot(const int& shottype)
{

	/*float rad = DirectX::XMConvertToRadians(m_horizontalAngle + 90.0f);
	DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));*/
	
	// �}�E�X�̍��W����������Z�o
	std::vector<GameObject*> reticule = GameContext<GameObjectManager>::Get()->Find("Pointer");
	DirectX::SimpleMath::Vector3 pointerPos = reticule.front()->GetPosition();
	DirectX::SimpleMath::Vector3 vec = pointerPos - m_position;
	vec.Normalize(); 

	switch (shottype)
	{
	case 0:
	{
		// �ʏ�e�ۂ𐶐�
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(m_position, vec);
		GameContext<GameObjectManager>::Get()->Add(std::move(bullet));

		break;
	}
	case 1:
	{
		// �`���[�W�e�ۂ𐶐�
		std::unique_ptr<ChargeShot> bullet = std::make_unique<ChargeShot>(m_position, vec,m_shotPower);
		GameContext<GameObjectManager>::Get()->Add(std::move(bullet));
		break;
	}
	default:
	{
		assert("�I�����ꂽ�e�ۂ����݂��܂���B");
		break;
	}
	}
	m_elapsedTime = 0.0f;
	m_isLoading = true;
}


