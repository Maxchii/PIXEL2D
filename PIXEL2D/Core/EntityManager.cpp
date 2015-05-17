#include "EntityManager.h"
#include "Entity.h"

namespace PIXL
{
	EntityManager::EntityManager(graphics::SpriteBatch* spriteBatch, graphics::Shader* shader, const math::Matrix4x4& projectionMatrix)
		: m_spriteBatch(spriteBatch), m_shader(shader), m_projectionMatrix(projectionMatrix)
	{
		m_shader->Enable();
		GLint texIDs[] =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		m_shader->SetUniform1iv("textures", texIDs, 32);
		m_shader->SetUniformMat4("pr_matrix", m_projectionMatrix);
		m_shader->Disable();
	}

	void EntityManager::Update(Float32 deltaTime)
	{
		//for (auto& e : entities) e->Update(deltaTime);

		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Update(deltaTime);
		}
	}

	void EntityManager::Draw()
	{
		//for (auto& e : entities) e->Draw();

		m_shader->Enable();
		m_spriteBatch->Begin();
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Draw(m_spriteBatch);
		}
		m_spriteBatch->End();
		m_spriteBatch->Flush();
	}

	void EntityManager::Refresh()
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

	EntityManager::~EntityManager()
	{

	}

}