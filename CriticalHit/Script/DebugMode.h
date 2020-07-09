// デバッグモード制御クラスのヘッダ
// 佐竹晴登

#pragma once
class DebugMode
{
private:
	bool m_mode;
private:
	DebugMode();
public:
	~DebugMode();
	// デバッグモードのセッタ
	void SetDebugMode(bool v);
	// デバッグモードのゲッタ
	bool GetDebugMode();
public:
	static DebugMode* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			// オブジェクトを生成して、ポインタを格納
			m_pInstance.reset(new DebugMode());
		}

		// オブジェクトへのポインタを返す
		return m_pInstance.get();
	}
private:
	static std::unique_ptr<DebugMode> m_pInstance;
};

