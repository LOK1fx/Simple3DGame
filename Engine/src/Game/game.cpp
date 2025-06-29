#include "game.h"

#include "Graphics/GraphicsEngine.h"
#include "Window/window.h"
#include "Graphics/vertexarrayobject.h"
#include "Graphics/shaderprogram.h"
#include "Graphics/uniformbuffer.h"
#include "Math/matrix44.h"
#include "Math/vector2.h"

#include "Entity/entitysystem.h"

#include <Windows.h>
#include <iostream>

namespace Engine
{
	struct UniformData
	{
		Matrix44 world;
		Matrix44 projection;
	};

	struct Vertex
	{
		Vec3 position;
		Vec2 texcoord;
	};

	Game::Game()
	{
		m_graphicsEngine = std::make_unique<GraphicsEngine>();
		m_window = std::make_unique<WindowsWindow>();
		m_entitySystem = std::make_unique<EntitySystem>();

		m_window->MakeCurrentContext();

		m_graphicsEngine->SetViewport(m_window->GetInnerSize());
	}

	Game::~Game()
	{
	}

	void Game::OnCreate()
	{
		Vec3 positionsList[] = {
			// Front face
			Vec3(-0.5f, -0.5f, -0.5f),
			Vec3(-0.5f, 0.5f, -0.5f),
			Vec3(0.5f, 0.5f, -0.5f),
			Vec3(0.5f, -0.5f, -0.5f),

			// Back face
			Vec3(0.5f, -0.5f, 0.5f),
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(-0.5f, 0.5f, 0.5f),
			Vec3(-0.5f, -0.5f, 0.5f),
		};

		Vec2 texcoordList[] = {
			Vec2(0, 0),
			Vec2(0, 1),
			Vec2(1, 0),
			Vec2(1, 1),
		};

		Vertex verticesList[] = {
			// Front
			{positionsList[0], texcoordList[1] },
			{positionsList[1], texcoordList[0] },
			{positionsList[2], texcoordList[2] },
			{positionsList[3], texcoordList[3] },

			// Back
			{positionsList[4], texcoordList[1] },
			{positionsList[5], texcoordList[0] },
			{positionsList[6], texcoordList[2] },
			{positionsList[7], texcoordList[3] },

			// Top
			{positionsList[1], texcoordList[1] },
			{positionsList[6], texcoordList[0] },
			{positionsList[5], texcoordList[2] },
			{positionsList[2], texcoordList[3] },

			// Bottom
			{positionsList[7], texcoordList[1] },
			{positionsList[0], texcoordList[0] },
			{positionsList[3], texcoordList[2] },
			{positionsList[4], texcoordList[3] },

			// Right
			{positionsList[3], texcoordList[1] },
			{positionsList[2], texcoordList[0] },
			{positionsList[5], texcoordList[2] },
			{positionsList[4], texcoordList[3] },

			// Left
			{positionsList[7], texcoordList[1] },
			{positionsList[6], texcoordList[0] },
			{positionsList[1], texcoordList[2] },
			{positionsList[0], texcoordList[3] },
		};

		ui32 indicesList[] = {
			// Front
			0, 1, 2,
			2, 3, 0,

			// Back
			4, 5, 6,
			6, 7, 4,

			// Top
			8, 9, 10,
			10, 11, 8,

			// Bottom
			12, 13, 14,
			14, 15, 12,

			// Right
			16, 17, 18,
			18, 19, 16,

			// Left
			20, 21, 22,
			22, 23, 20
		};


		VertexAttribute attributeList[] = {
			sizeof(Vec3) / sizeof(f32), // position
			sizeof(Vec2) / sizeof(f32), // texcoord
		};

		VertexBufferDesc vbDesc = {};
		vbDesc.verticesList = (void*)verticesList;
		vbDesc.vertexSize = sizeof(Vertex);
		vbDesc.listSize = sizeof(verticesList)/sizeof(Vertex);
		vbDesc.attributeList = attributeList;
		vbDesc.attributesListSize = sizeof(attributeList)/sizeof(VertexAttribute);

		IndexBufferDesc ibDesc = {};
		ibDesc.indicesList = indicesList;
		ibDesc.listSize = sizeof(indicesList);

		m_polygonVAO = m_graphicsEngine->CreateVertexArrayObject(vbDesc, ibDesc);
		
		
		UniformBufferDesc uBufferDesc = {};
		uBufferDesc.size = sizeof(UniformData);

		m_uniformBuffer = m_graphicsEngine->CreateUniformBuffer(uBufferDesc);


		ShaderProgramDesc shaderDesc = {};
		shaderDesc.vertexShaderFilePath = L"Assets/Shaders/BasicShader.vert";
		shaderDesc.fragmentShaderFilePath = L"Assets/Shaders/BasicShader.frag";

		m_shaderProgram = m_graphicsEngine->CreateShaderProgram(shaderDesc);

		m_shaderProgram->SetUniformBufferSlot("UniformData", 0);
	}

	void Game::OnUpdateInternal()
	{
		auto currentTime = std::chrono::system_clock::now();
		auto elsapsedSeconds = std::chrono::duration<double>();

		if (m_previousTime.time_since_epoch().count())
		{
			elsapsedSeconds = currentTime - m_previousTime;
		}
		m_previousTime = currentTime;

		auto deltaTime = (f32)elsapsedSeconds.count();


		OnUpdate(deltaTime);
		m_entitySystem->Update(deltaTime);




		m_scale += 3.14f * 0.5f * deltaTime;
		auto currentScale = abs(sin(m_scale));

		Matrix44 world;
		Matrix44 projection;
		Matrix44 temp;

		// Scale
		temp.SetIdentity();
		temp.SetScale(Vec3(currentScale, currentScale, currentScale));
		world *= temp;


		// Rotation
		temp.SetIdentity();
		temp.SetRotationZ(m_scale * 0.5f);
		world *= temp;

		temp.SetIdentity();
		temp.SetRotationY(m_scale * 1);
		world *= temp;

		temp.SetIdentity();
		temp.SetRotationX(m_scale * 1);
		world *= temp;


		// Translation
		temp.SetIdentity();
		temp.SetTranslation(Vec3(0, 0, 0));
		world *= temp;

		Rect windowRect = m_window->GetInnerSize();
		f32 rectFactor = 0.004f;
		projection.SetOrthoLH(windowRect.Width * rectFactor, windowRect.Height * rectFactor, 0.03f, 1000);


		UniformData data = { world, projection };
		m_uniformBuffer->SetData(&data);

		m_graphicsEngine->Clear(Vec4(0.4f, 0.55f, 0.85f, 0));

		m_graphicsEngine->SetFaceCulling(CullType::BackFace);
		m_graphicsEngine->SetWindingOrder(WindingOrderType::ClockWise);

		m_graphicsEngine->SetVertexArrayObject(m_polygonVAO);
		m_graphicsEngine->SetUniformBuffer(m_uniformBuffer, 0);
		m_graphicsEngine->SetShaderProgram(m_shaderProgram);
		m_graphicsEngine->DrawIndexedTriangles(TriangleType::TriangleList, 36);

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

			OnUpdateInternal();
		}

		OnQuit();

		std::cout << "Game closed." << std::endl;
	}

	void Game::Quit()
	{
	}
}
