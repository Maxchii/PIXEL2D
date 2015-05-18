#include "Game.h"
#include "Utilities/StringExtensions.h"
#include "Core/Transform.h"
#include "Graphics/Sprite.h"
#include "Input/KeyboardInput.h"

void Game::Init()
{
	window = CreateWindow("Game", 1280, 720, NULL);
	window->EnableVsync(false);

	texture = new graphics::Texture("Assets/sheet.png");
	shader = new graphics::Shader("Assets/basic.vert", "Assets/basic.frag");

	manager = new EntityManager(new graphics::SpriteBatch(), shader, math::Matrix4x4::Orthographic(0, window->Width(), window->Height(), 0, -1.0f, 1.0f));

	float textureW = 32.0;
	float textureH = 32.0f;

	for (int y = 0; y < (window->Height() / textureH); y++)
	{
		for (int x = 0; x < (window->Width() / textureW); x++)
		{
			auto& ent(manager->AddEntity());
			ent.AddComponent<Sprite>(*texture, math::Rectangle(0, 0, 32, 32), math::Vector2(32, 32), math::Vector4(1, 1, 1, 1));
			
			ent.GetTransform().SetPosition(math::Vector2(textureW / 2 + x * textureW, textureH / 2 + y * textureH));
			ent.GetTransform().SetRotation(0);
			ent.GetTransform().SetScale(math::Vector2(1, 1));
		}
	}
	std::cout << "Textures on screen: " << (int)(window->Width() / textureW * window->Height() / textureH) << std::endl;


	auto& ent(manager->AddEntity());
	ent.AddComponent<Drawable>(math::Vector2(150,30), math::Vector4(0, 0, 0, 0.85f));
	ent.GetTransform().SetPosition(math::Vector2(window->Width()-75,window->Height()-15));
	ent.GetTransform().SetRotation(0);
	ent.GetTransform().SetScale(math::Vector2(1, 1));
	audioClip = &ent.AddComponent<AudioClip>("Assets/Witching Hour.mp3", true);
	testEntity = &ent;

	auto& ent2(manager->AddEntity());
	ent2.GetTransform().SetPosition(math::Vector2(-75, 12));
	label =  &ent2.AddComponent<Label>("Assets/Nunito-Bold.ttf", "FPS", math::Vector4(1.0f, .62f, 0.0f, 1), 32);
	ent2.SetParent(ent);
	

}

void Game::Update(float deltaTime)
{
	if (input::KeyboardInput::GetKeyDown(GLFW_KEY_1))
	{
		audioClip->Play();
	}

	if (input::KeyboardInput::GetKeyDown(GLFW_KEY_2))
	{
		audioClip->Pause();
	}

	if (input::KeyboardInput::GetKeyDown(GLFW_KEY_3))
	{
		audioClip->Stop();
	}

	label->SetText(std::to_string(Time::GetFps()).append(" FPS"));

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
