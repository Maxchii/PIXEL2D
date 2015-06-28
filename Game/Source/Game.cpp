#include "Game.h"
#include "Utilities/StringExtensions.h"
#include "Core/Transform.h"
#include "Graphics/Sprite.h"
#include "Input/KeyboardInput.h"
#include "Physics/Collider.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void Game::Init()
{
	window = CreateWindow("Game", WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
	window->EnableVsync(false);

	texture = new graphics::Texture("Assets/sheet.png", graphics::TextureWrap::CLAMP_TO_EDGE, graphics::TextureWrap::CLAMP_TO_EDGE,graphics::TextureFilter::LINEAR, graphics::TextureFilter::LINEAR_MIPMAP_LINEAR);
	shader = new graphics::Shader("Assets/basic.vert", "Assets/basic.frag");

	manager = CreateLayer(math::Matrix4x4::Orthographic(0, window->Width(), window->Height(), 0, -1.0f, 1.0f),shader,0.0f);

	float textureW = 32.0f;
	float textureH = 32.0f;

	for (int y = 0; y < (window->Height() / textureH); y++)
	{
		for (int x = 0; x < (window->Width() / textureW); x++)
		{
			auto& ent(manager->AddEntity());
			ent.AddComponent<Sprite>(*texture, math::Rectangle(0, 0, 32, 32), math::Vector2f(textureW, textureH), math::Vector4f(1, 1, 1, 1));
			
			ent.GetTransform().SetPosition(math::Vector2f(textureW / 2 + x * textureW, textureH / 2 + y * textureH));
			ent.GetTransform().SetRotation(0);
			ent.GetTransform().SetScale(math::Vector2f(1, 1));
		}
	}
	std::cout << "Textures on screen: " << (int)(window->Width() / textureW * window->Height() / textureH) << std::endl;


	auto& ent(manager->AddEntity());
	ent.AddComponent<Drawable>(math::Vector2f(150, 30), math::Vector4f(0, 0, 0, 0.85f));
	ent.GetTransform().SetPosition(math::Vector2f(window->Width() / 2 - 75, window->Height() / 2 - 15));
	ent.GetTransform().SetRotation(-5);
	ent.GetTransform().SetScale(math::Vector2f(1, 1));
	
	testEntity = &ent;

	auto& ent2(manager->AddEntity());
	ent2.GetTransform().SetPosition(math::Vector2f(-75, 12));
	label =  &ent2.AddComponent<Label>("Assets/Nunito-Bold.ttf", "FPS", math::Vector4f(1.0f, .62f, 0.0f, 1), 32);
	ent2.SetParent(ent);
}

void Game::Update(float deltaTime)
{

	label->SetText(std::to_string(Time::GetFps()).append(" FPS"));
	float rot = testEntity->GetTransform().GetRotation();
	testEntity->GetTransform().SetRotation(rot += 20 * deltaTime);
}

Game::~Game()
{

}
