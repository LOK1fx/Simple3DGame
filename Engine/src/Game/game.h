#pragma once

#include "prerequisites.h"
#include <memory>
#include <chrono>

namespace Engine
{
	class GraphicsEngine;
	class EntitySystem;
	class WindowsWindow;

	class Game
	{
	public:
		Game();
		virtual ~Game();

		void Run();
		void Quit();

		EntitySystem* GetEntitySystem() const { return m_entitySystem.get(); }

	protected:
		virtual void OnCreate();
		virtual void OnUpdate(f32 deltaTime) { }
		virtual void OnQuit();

		bool m_isRunning = true;
		f32 m_scale = 0;

		std::chrono::system_clock::time_point m_previousTime;

		std::unique_ptr<GraphicsEngine> m_graphicsEngine;
		std::unique_ptr<WindowsWindow> m_window;
		std::unique_ptr<EntitySystem> m_entitySystem;

		VertexArrayObjectPtr m_polygonVAO;
		UniformBufferPtr m_uniformBuffer;
		ShaderProgramPtr m_shaderProgram;

	private:
		void OnUpdateInternal();
	};
}
