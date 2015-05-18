#include "Game.h"
#include "Utilities/StringExtensions.h"
#include "Core/Transform.h"

void Game::Init()
{
	window = CreateWindow("Game", 1280, 720, NULL);
	window->EnableVsync(false);


	texture = new graphics::Texture("Assets/pxl2d.png");
	shader = new graphics::Shader("Assets/basic.vert", "Assets/basic.frag");

	manager = new EntityManager(new graphics::SpriteBatch(), shader, math::Matrix4x4::Ortho(0, 1280, 720, 0, -1.0f, 1.0f));


	/*float textureW = 32;
	float textureH = 32.0f;

	for (int y = 0; y < (window->Height() / textureH); y++)
	{
		for (int x = 0; x < (window->Width() / textureW); x++)
		{
			auto& ent(manager->AddEntity());
			ent.AddComponent<Drawable>(*texture, math::Vector4(1,0,0,1));
			
			ent.GetTransform().SetPosition(math::Vector2(textureW / 2 + x * textureW, textureH / 2 + y * textureH));
			ent.GetTransform().SetRotation(0);
			ent.GetTransform().SetScale(math::Vector2(1, 1));
		}
	}
	std::cout << "Textures on screen: " << (int)(window->Width() / textureW * window->Height() / textureH) << std::endl;*/

	auto& ent(manager->AddEntity());
	ent.AddComponent<Drawable>(*texture, math::Vector4(1, 0, 0, 1));

	ent.GetTransform().SetPosition(math::Vector2(100,100));
	ent.GetTransform().SetRotation(0);
	ent.GetTransform().SetScale(math::Vector2(1, 1));

	auto& ent2(manager->AddEntity());
	ent2.AddComponent<Drawable>(*texture, math::Vector4(1, 0, 0, 1));

	ent2.GetTransform().SetPosition(math::Vector2(500,500));
	ent2.GetTransform().SetRotation(0);
	ent2.GetTransform().SetScale(math::Vector2(1, 1));
	ent.SetParent(ent);

}

void Game::Update(float deltaTime)
{
	manager->Refresh();
	manager->Update(deltaTime);
}

void Game::Render()
{
	manager->Draw();
}

Game::~Game()
{

}
