#include "game.h"

#include "Graphics/GraphicsEngine.h"
#include "Window/window.h"
#include "Graphics/vertexarrayobject.h"

#include <Windows.h>
#include <iostream>

namespace Engine
{
	Game::Game()
	{
		m_graphicsEngine = std::make_unique<GraphicsEngine>();
		m_window = std::make_unique<WindowsWindow>();

		m_window->MakeCurrentContext();

		m_graphicsEngine->SetViewport(m_window->GetInnerSize());
	}

	Game::~Game()
	{
	}

	void Game::OnCreate()
	{
		const f32 triangleVertices[] = {
			-0.5f, -0.5f, 0.0f,
			1,	0,	0,

			0.5f, -0.5f, 0.0f,
			0,	1,	0,
			
			0.0f, 0.5f, 0.0f,
			0,	0, 1,
		};

		VertexAttribute attributeList[] = {
			3, // position
			3 // color
		};

		VertexBufferDesc data = {};
		data.verticesList = (void*)triangleVertices;
		data.vertexSize = sizeof(f32) * (3+3);
		data.listSize = 3;
		data.attributeList = attributeList;
		data.attributesListSize = 2;


		m_triangleVAO = m_graphicsEngine->CreateVertexArrayObject(data);
		
		ShaderProgramDesc shaderDesc = {};
		shaderDesc.vertexShaderFilePath = L"Assets/Shaders/BasicShader.vert";
		shaderDesc.fragmentShaderFilePath = L"Assets/Shaders/BasicShader.frag";


		m_shader = m_graphicsEngine->CreateShaderProgram(shaderDesc);
	}

	void Game::OnUpdate()
	{
		m_graphicsEngine->Clear(Vec4(0.4f, 0.55f, 0.85f, 0));
		m_graphicsEngine->SetVertexArrayObject(m_triangleVAO);
		m_graphicsEngine->SetShaderProgram(m_shader);
		m_graphicsEngine->DrawTriangles(m_triangleVAO->GetVertexBufferSize(), 0);

		m_window->Present(false);
	}

	void Game::OnQuit()
	{
	}

	void Game::Run()
	{
		OnCreate();

		MSG message = {};
		while (m_isRunning)
		{
			if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
			{
				if (message.message == WM_QUIT)
				{
					m_isRunning = false;
					break;
				}

				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			OnUpdate();
		}

		OnQuit();

		std::cout << "Game closed." << std::endl;
	}

	void Game::Quit()
	{
	}
}
