#include "Game.h"
#include "Utilities/StringExtensions.h"
#include "Core/Transform.h"

void Game::Init()
{
	window = CreateWindow("Game", 1280, 720, NULL);
	window->EnableVsync(false);


	texture = new graphics::Texture("Assets/wall.png");
	shader = new graphics::Shader("Assets/basic.vert", "Assets/basic.frag");

	manager = new EntityManager(new graphics::SpriteBatch(), shader, math::Matrix4x4::Ortho(0, 640, 360, 0, -1.0f, 1.0f));

	auto& ent(manager->addEntity());
	ent.AddComponent<Drawable>(*texture, math::Vector4::One());
	Transform& t = ent.AddComponent<Transform>();
	t.SetPosition(math::Vector2(1500,500.0f));
	//t.Rotate(0.5f);
	//t.Scale(math::Vector2(1, 2));

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
