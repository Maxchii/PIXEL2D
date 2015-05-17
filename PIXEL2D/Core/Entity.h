#pragma once
#include "ValueTypes.h"
#include "Component.h"

#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include <cassert>


namespace PIXL{

	inline std::size_t GetUniqueComponentID()
	{
		static std::size_t  lastID{ 0u };
		return lastID++;
	}

	template<typename T> inline std::size_t  GetComponentTypeID()
	{
		static_assert(std::is_base_of<Component, T>::value,
			"T must inherit from Component");

		static std::size_t  typeID{ GetUniqueComponentID() };
		return typeID;
	}

	class EntityManager;
	class Component;
	class Entity
	{
	public:
		Entity(EntityManager& entManager);

		void Update(Float32 deltaTime);
		void Draw();

		bool IsAlive() const;
		void Destroy();

		template<typename T> bool HasComponent() const
		{
			return m_componentBitSet[GetComponentTypeID<T>()];
		}

		template<typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs)
		{
			assert(!HasComponent<T>());

			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			m_components.emplace_back(std::move(uPtr));

			m_componentsArray[GetComponentTypeID<T>()] = c;
			m_componentBitSet[GetComponentTypeID<T>()] = true;

			c->Init();
			return *c;
		}

		template<typename T> T& GetComponent() const
		{
			assert(HasComponent<T>());
			auto ptr(m_componentsArray[GetComponentTypeID<T>()]);
			return *reinterpret_cast<T*>(ptr);
		}

	private:
		EntityManager& m_manager;
		bool m_alive;
		std::vector<std::unique_ptr<Component>> m_components;
		std::array<Component*, 32> m_componentsArray;
		std::bitset<32> m_componentBitSet;
	};

}