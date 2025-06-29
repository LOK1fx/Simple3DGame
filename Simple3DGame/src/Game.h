#pragma once

#include <engine.h>

#include "Entities/Player.h"

class Game : public Engine::Game
{
public:
	Game();
	~Game();

	virtual void OnCreate() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnQuit() override;

private:
	Player* m_player = nullptr;
};

