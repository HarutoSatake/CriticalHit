#pragma once


#include "..\..\GameObject\GameObject.h"
#include <vector>
class EnemyGenerator :
	public GameObject
{
private:
	enum EnemyList
	{
		NORMAL,
		SIDE,
		WAVE,

		SUM
	};
private:
	float m_interval;
	float m_elapsedTime;

public:
	EnemyGenerator(float interval);
	~EnemyGenerator();
public:
	void Update(float elapsedTime) override;
	void Render() override;

	void Generate() const;
	void OnCollision(GameObject* object) override;

private:
	int m_enemyList;
	int m_lastScore;
};

