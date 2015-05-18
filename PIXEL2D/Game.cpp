#include "Game.h"
#include "Utilities/StringExtensions.h"
#include "Core/Transform.h"

void Game::Init()
{
	window = CreateWindow("Game", 1280, 720, NULL);
	window->EnableVsync(false);


	texture = new graphics::Texture("Assets/wall.png");
	shader = new graphics::Shader("Assets/basic.vert", "Assets/basic.frag");

	manager = new EntityManager(new graphics::SpriteBatch(), shader, math::Matrix4x4::Orthographic(0, 1280, 720, 0, -1.0f, 1.0f));


	float textureW = 32.0;
	float textureH = 32.0f;

	for (int y = 0; y < (window->Height() / textureH); y++)
	{
		for (int x = 0; x < (window->Width() / textureW); x++)
		{
			auto& ent(manager->AddEntity());
			ent.AddComponent<Drawable>(*texture, math::Vector4(1,1,1,1));
			
			ent.GetTransform().SetPosition(math::Vector2(textureW / 2 + x * textureW, textureH / 2 + y * textureH));
			ent.GetTransform().SetRotation(0);
			ent.GetTransform().SetScale(math::Vector2(1, 1));
		}
	}
	std::cout << "Textures on screen: " << (int)(window->Width() / textureW * window->Height() / textureH) << std::endl;

	

	auto& ent(manager->AddEntity());
	ent.AddComponent<Drawable>(*texture, math::Vector4(1, 0, 0, 1));

	ent.GetTransform().SetPosition(math::Vector2(200,200));
	ent.GetTransform().SetRotation(0);
	ent.GetTransform().SetScale(math::Vector2(1, 1));
	audioClip = &ent.AddComponent<AudioClip>("Assets/Witching Hour.mp3", true);
	testEntity = &ent;

	auto& ent2(manager->AddEntity());
	ent2.AddComponent<Drawable>(*texture, math::Vector4(0, 1, 0, 1));

	ent2.GetTransform().SetPosition(math::Vector2(32, 32));
	ent2.GetTransform().SetRotation(0);
	ent2.GetTransform().SetScale(math::Vector2(1.0f, 1.0f));
	ent.AddComponent<Label>("Assets/Nunito-Bold.ttf", "PIXEL 2D!!@#$!@$", math::Vector4(1.0f, .62f, 0.0f, 1), 32);
	ent2.SetParent(ent);

	auto& ent3(manager->AddEntity());
	ent3.AddComponent<Drawable>(*texture, math::Vector4(0, 1, 0, 1));

	ent3.GetTransform().SetPosition(math::Vector2(32, 32));
	ent3.GetTransform().SetRotation(0);
	ent3.GetTransform().SetScale(math::Vector2(1.0f, 1.0f));
	ent3.AddComponent<Label>("Assets/Nunito-Bold.ttf", "PIXEL 2D!!@#$!@$", math::Vector4(1.0f, .62f, 0.0f, 1), 32);
	ent3.SetParent(ent2);

}

void Game::Update(float deltaTime)
{
	float rot = testEntity->GetTransform().GetRotation();
	testEntity->GetTransform().SetRotation(rot += 20.0f * deltaTime);

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
