#pragma once

#include "StepTimer.h"
#include "GameContext.h"
#include "GameSceneManager.h"
class GameScene
{
public:
	GameScene() = default;

public:
	virtual ~GameScene() = default;

public:
	virtual void Initialize() = 0;
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};