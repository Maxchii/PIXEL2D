#include "EntityManager.h"
#include "Entity.h"

namespace PIXL
{
	void EntityManager::Update(Float32 deltaTime)
	{
		for (auto& e : entities) e->Update(deltaTime);
	}

	void EntityManager::Draw()
	{
		for (auto& e : entities) e->Draw();
	}

	void EntityManager::refresh()
	{
		// During refresh, we need to remove dead entities and entities

		entities.erase(
			std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
		{
			return !mEntity->IsAlive();
		}),
			std::end(entities));
	}

	Entity& EntityManager::addEntity()
	{
		Entity* e(new Entity(*this));
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

}