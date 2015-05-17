#include "Game.h"
#include "Utilities/StringExtensions.h"

void Game::Init()
{
	window = CreateWindow("Game", 1280, 720, NULL);
	window->EnableVsync(false);

	audioClip = new audio::AudioClip("Assets/Witching Hour.mp3", true);
	//audioClip->Play();

	texture = new graphics::Texture("Assets/testCat.png");
	shader = new graphics::Shader("Assets/basic.vert", "Assets/basic.frag");



	layer = new graphics::Layer(new graphics::SpriteBatch(), shader, math::Matrix4x4::Ortho(0, 1280, 720, 0, -1.0f, 1.0f));
	layer->Add(new Label("Assets/Nunito-Bold.ttf", "PIXEL 2D", math::Vector4(1.0f, .62f, 0.0f, 1), 64));

	/*Float32 textureW = 32.0f;
	Float32 textureH = 32.0f;

	for (int y = 0; y < window->Height() / textureH; y++)
	{
		for (int x = 0; x < window->Width() / textureW; x++)
		{
			Drawable* sprite = new Drawable();

		}
	}*/

	drawable = new graphics::Drawable(*texture, math::Vector4::One());
	layer->Add(drawable);

	
	

}

void Game::Update(float deltaTime)
{
}

void Game::Render()
{
	layer->Draw();
	
}

Game::~Game()
{

}
