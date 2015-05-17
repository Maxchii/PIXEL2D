#pragma once
#include "ValueTypes.h"
#include <vector>
#include <memory>

namespace PIXL
{
	class Entity;
	struct EntityManager
	{
	public:
		void Update(Float32 deltaTime);
		void Draw();
		void refresh();

		Entity& addEntity();

	private:
		std::vector<std::unique_ptr<Entity>> entities;
	};
}