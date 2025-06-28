#pragma once

#include <memory>
#include "Graphics/GraphicsEngine.h"

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

		std::unique_ptr<GraphicsEngine> m_graphicsEngine;
		std::unique_ptr<WindowsWindow> m_window;

		VertexArrayObjectPtr m_triangleVAO;
	};
}
