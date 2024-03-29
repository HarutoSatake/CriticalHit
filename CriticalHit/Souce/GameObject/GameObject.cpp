// ゲームオブジェクトクラスのソース
// 佐竹晴登

// ヘッダインクルード
#include "..\pch.h"

#include "GameObject.h"



GameObject::GameObject(const std::string& tag)
	: m_isValid(true)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_tag(tag)
	, m_debugMode(false)
{
}

void GameObject::Invalidate()
{
	m_isValid = false;
}
