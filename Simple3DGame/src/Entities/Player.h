#pragma once

#include "engine.h"

class Player : public Engine::Entity
{
public:
	Player() = default;
	~Player() = default;

protected:
	virtual void OnCreate() override;
	virtual void OnUpdate(float deltaTime) override;
};

