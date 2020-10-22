// �Q�[�����C���N���X�̃w�b�_
// 2019/06/18
// ���|���o

#pragma once

// �w�b�_�C���N���[�h
#include "DeviceResources.h"
#include "StepTimer.h"
#include "Projection.h"
#include <Keyboard.h>
#include <Mouse.h>
#include <CommonStates.h>

#include "GameObject\DebugCamera.h"
#include "GameObject\GridFloor.h"
#include "Manager\GameSceneManager.h"
#include "Manager\GameObjectManager.h"
#include "Manager\CollisionManager.h"
#include "Manager\EffectManager.h"
#include "UI\Font.h"
#include "Adx2Le.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // �f�o�C�X���\�[�X
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_pMouse;
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>		m_pKeyBoard;
	// �L�[�{�[�h�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_pKeyStateTracker;
	
	// �ˉe�s��
 	std::unique_ptr<Projection>			    m_projection;
	// �V�[���}�l�[�W���[
	std::unique_ptr<GameSceneManager>		m_pGameSceneManager;
	// �R���W�����}�l�[�W���[
	std::unique_ptr<CollisionManager>		m_pCollisionManager;
	
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>			m_pSprite;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>			m_pStates;

	DirectX::SimpleMath::Vector3			m_camera;
	DirectX::SimpleMath::Matrix				m_view;
	// �G�t�F�N�g�}�l�[�W���[
	std::unique_ptr<EffectManager>			m_pEffectManager;
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect>	m_pBasicEffect;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	// �T�E���h�p
	std::unique_ptr<Adx2Le>						m_pAdx2le;
};