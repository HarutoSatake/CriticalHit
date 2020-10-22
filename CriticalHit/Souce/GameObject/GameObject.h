// ゲームオブジェクトの基底クラスのヘッダ
// 佐竹晴登

#pragma once

// ヘッダインクルード
#include <SimpleMath.h>
#include <string>
#include "..\GameContext.h"
#include "..\Projection.h"
#include "..\DebugMode.h"

// ゲームオブジェクトクラス
class GameObject
{
private:
	bool m_isValid;


protected:
	DirectX::SimpleMath::Vector3 m_position;	// 座標
	DirectX::SimpleMath::Vector3 m_rotation;	// 回転
	DirectX::SimpleMath::Vector3 m_scale;		// 大きさ
	std::string					 m_tag;			// タグ
	bool						 m_debugMode;	// デバッグモードか否か

public:
	// コンストラクタ
	GameObject(const std::string& tag = "GameObject");
public:
	// デストラクタ
	virtual ~GameObject() = default;

// 公開処理
public:
	// 更新処理
	virtual void Update(float elapsedTime) = 0;
	// 描画処理
	virtual void Render() = 0;
	// 当たり判定処理
	virtual void OnCollision(GameObject* object) = 0;
// ゲッタとセッタ
public:
	// 非表示にする
	void Invalidate();
	// 表示する
	bool IsValid() const;
	// 非表示にする
	bool IsInvalid() const;

	// 現在のタグを取得
	const std::string& GetTag() const;
	// 現在の座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	// 現在の回転値を取得
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	// 現在の大きさを取得
	const DirectX::SimpleMath::Vector3& GetScale() const;

	// 現在座標を設定
	void SetPosition(DirectX::SimpleMath::Vector3& position);
	// 現在の回転値を設定
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	// 現在の大きさを設定
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	// 現在のデバッグモードか否かを設定
	void SetDebugMode(const bool& value);
// 汎用関数
public:
	// 目的地まで等速直線移動(移動が完了したらtrueを返す)
	// 引数(Vector3 目的地座標、float 移動する速度)
	bool Translate(const DirectX::SimpleMath::Vector3& dest,const float& speed);
	// 目的の値まで等速で回転する(回転が完了したらtrueを返す)
	// 引数(Vector3 目的回転値 float 回転速度)
	bool Rotation(const DirectX::SimpleMath::Vector3& angle, const float& speed);


public:
	// ゲームオブジェクトを削除する
	// 引数(削除するオブジェクト)
	static void Destroy(GameObject* object);
};
// 表示にする
inline bool GameObject::IsValid() const
{
	return m_isValid;
}
// 非表示にする
inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}
// 現在の座標を取得
inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}
// 現在の回転値を取得
inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}
// 現在の大きさを取得
inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}
// 現在のタグを取得
inline const std::string & GameObject::GetTag() const
{
	return m_tag;
}
// 現在の座標を設定
inline void GameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}
// 現在の回転値を設定
inline void GameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}
// 現在の大きさを設定
inline void GameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}
// ゲームオブジェクトを削除する
inline void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}
// デバッグモードを設定
inline void GameObject::SetDebugMode(const bool& value)
{
	m_debugMode = value;
}