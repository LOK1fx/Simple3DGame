#include "game.h"

#include "Graphics/GraphicsEngine.h"
#include "Window/window.h"
#include "Graphics/vertexarrayobject.h"
#include "Graphics/shaderprogram.h"
#include "Graphics/uniformbuffer.h"

#include <Windows.h>
#include <iostream>

namespace Engine
{
	struct UniformData
	{
		f32 scale;
	};

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
		const f32 polygonVertices[] = {
			-0.5f, -0.5f, 0.0f,
			1,	0,	0,

			-0.5f, 0.5f, 0.0f,
			0,	1,	0,
			
			0.5f, -0.5f, 0.0f,
			0,	0, 1,

			0.5f, 0.5f, 0.0f,
			1,	1, 0,
		};

		VertexAttribute attributeList[] = {
			3, // position
			3 // color
		};

		VertexBufferDesc data = {};
		data.verticesList = (void*)polygonVertices;
		data.vertexSize = sizeof(f32) * (3+3);
		data.listSize = 4;
		data.attributeList = attributeList;
		data.attributesListSize = 2;

		m_polygonVAO = m_graphicsEngine->CreateVertexArrayObject(data);
		
		
		UniformBufferDesc uBufferDesc = {};
		uBufferDesc.size = sizeof(UniformData);

		m_uniformBuffer = m_graphicsEngine->CreateUniformBuffer(uBufferDesc);


		ShaderProgramDesc shaderDesc = {};
		shaderDesc.vertexShaderFilePath = L"Assets/Shaders/BasicShader.vert";
		shaderDesc.fragmentShaderFilePath = L"Assets/Shaders/BasicShader.frag";

		m_shaderProgram = m_graphicsEngine->CreateShaderProgram(shaderDesc);

		m_shaderProgram->SetUniformBufferSlot("UniformData", 0);
	}

	void Game::OnUpdate()
	{
		auto currentTime = std::chrono::system_clock::now();
		auto elsapsedSeconds = std::chrono::duration<double>();

		if (m_previousTime.time_since_epoch().count())
		{
			elsapsedSeconds = currentTime - m_previousTime;
		}
		m_previousTime = currentTime;

		auto deltaTime = (f32)elsapsedSeconds.count();

		m_scale += 3.14f * 0.5f * deltaTime;
		auto currentScale = abs(sin(m_scale));


		UniformData data = { currentScale };
		m_uniformBuffer->SetData(&data);

		m_graphicsEngine->Clear(Vec4(0.4f, 0.55f, 0.85f, 0));

		m_graphicsEngine->SetVertexArrayObject(m_polygonVAO);
		m_graphicsEngine->SetUniformBuffer(m_uniformBuffer, 0);
		m_graphicsEngine->SetShaderProgram(m_shaderProgram);
		m_graphicsEngine->DrawTriangles(TriangleStrip, m_polygonVAO->GetVertexBufferSize(), 0);

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
