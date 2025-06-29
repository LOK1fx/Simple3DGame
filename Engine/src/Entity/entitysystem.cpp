#include "entitysystem.h"
#include "Entity/entity.h"


namespace Engine
{
	EntitySystem::EntitySystem()
	{
	}
	EntitySystem::~EntitySystem()
	{
	}

	bool EntitySystem::CreateEntityInternal(Entity* entity, size_t id)
	{
		auto ptr = std::unique_ptr<Entity>(entity);
		m_entities[id].emplace(entity, std::move(ptr));

		entity->m_id = id;
		entity->m_entitySystem = this;
		entity->OnCreate();

		return true;
	}

	void EntitySystem::RemoveEntity(Entity* entity)
	{
		m_entitiesToDestroy.emplace(entity);
	}

	void EntitySystem::Update(f32 deltaTime)
	{
		for (auto entity : m_entitiesToDestroy)
		{
			m_entities[entity->m_id].erase(entity);
		}
		m_entitiesToDestroy.clear();

		for (auto&& [id, entities] : m_entities)
		{
			for (auto&& [ptr, entity] : entities)
			{
				entity->OnUpdate(deltaTime);
			}
		}
	}
}