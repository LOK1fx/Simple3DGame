#include "entity.h"
#include "entitysystem.h"


namespace Engine
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::Release()
	{
		m_entitySystem->RemoveEntity(this);
	}
}