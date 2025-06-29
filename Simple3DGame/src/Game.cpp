#include "Game.h"


Game::Game()
{

}

Game::~Game()
{

}

void Game::OnCreate()
{
	Engine::Game::OnCreate();

	m_player = GetEntitySystem()->CreateEntity<Player>();
}

void Game::OnUpdate(float deltaTime)
{
	
}

void Game::OnQuit()
{
	Engine::Game::OnQuit();

	m_player->Release();
	m_player = nullptr;
}