// デバッグモード制御クラスのソース

#include "pch.h"
#include "DebugMode.h"


std::unique_ptr<DebugMode> DebugMode::m_pInstance = nullptr;

DebugMode::DebugMode()
{
	m_mode = false;
}


DebugMode::~DebugMode()
{
}

void DebugMode::SetDebugMode(bool v)
{
	m_mode = v;
}

bool DebugMode::GetDebugMode()
{
	return m_mode;
}
