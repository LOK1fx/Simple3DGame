#include "Game.h"

#define ENTITY_CREATE(type) GetEntitySystem()->CreateEntity<type>();
#define ENTITY_RELEASE(x) { x->Release(); x = nullptr; }

Game::Game()
{

}

Game::~Game()
{

}

void Game::OnCreate()
{
	Engine::Game::OnCreate();

	//m_player = GetEntitySystem()->CreateEntity<Player>();
	m_player = ENTITY_CREATE(Player);
}

void Game::OnUpdate(float deltaTime)
{
	
}

void Game::OnQuit()
{
	Engine::Game::OnQuit();

	ENTITY_RELEASE(m_player);
}