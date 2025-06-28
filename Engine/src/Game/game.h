#pragma once

#include <memory>
#include "Graphics/GraphicsEngine.h"
#include <chrono>

namespace Engine
{
	class GraphicsEngine;
	class WindowsWindow;

	class Game
	{
	public:
		Game();
		~Game();

		virtual void OnCreate();
		virtual void OnUpdate();
		virtual void OnQuit();

		void Run();
		void Quit();

	protected:
		bool m_isRunning = true;
		f32 m_scale = 0;

		std::chrono::system_clock::time_point m_previousTime;

		std::unique_ptr<GraphicsEngine> m_graphicsEngine;
		std::unique_ptr<WindowsWindow> m_window;

		VertexArrayObjectPtr m_polygonVAO;
		UniformBufferPtr m_uniformBuffer;
		ShaderProgramPtr m_shaderProgram;
	};
}
