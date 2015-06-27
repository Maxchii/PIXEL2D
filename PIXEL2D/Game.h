#pragma once
#include "Core/PIXL2D.h"
#include "Audio/AudioClip.h"
#include "Graphics/Texture.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Shader.h"
#include "Graphics/Drawable.h"
#include "Graphics/Layer.h"
#include "Graphics/Label.h"
#include "Graphics/Font.h"
#include "Core/EntityManager.h"
#include "Core/Entity.h"
#include "Core/Component.h"

using namespace PIXL;
using namespace graphics;
using namespace audio;

class Game : public PIXL::PIXL2D
{
public:
	Game(){}
	~Game();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	Window* window;
	graphics::Texture* texture;
	graphics::Shader* shader;
	graphics::Drawable* drawable;
	graphics::Layer* layer;
	graphics::Label* label;
	graphics::Font* font;
	EntityManager* manager;
	Entity* testEntity;

};
