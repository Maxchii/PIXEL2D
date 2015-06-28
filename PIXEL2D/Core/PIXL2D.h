#pragma once
#include <vector>
#include "..//Graphics/Window.h"
#include "..//Input/KeyboardInput.h"
#include "..//Audio/Audio.h"
#include "..//Physics/Physics.h"
#include "Time.h"
#include "Layer.h"

namespace PIXL
{
	/*!
	* \brief This is the main type for your game.
	*
	* %PXL2D allows the user to create a new window and override the init, update and render functions,
	* it also updates the Window, game, collision system and rendering each frame.
	*
	*/
	class PIXL2D
	{
	public:
		/*!
		* \brief Starts PIXL2D
		*
		* start calls \ref init and starts the main game loop.
		*/
		void Start();

	protected:
		PIXL2D(){}
		virtual ~PIXL2D();

		/*!
		* \brief Creates and returns a new Window with the given parameters.
		*
		* <param name="windowHandle">Specify a window handle</param>
		* <param name="width">Specify the window width in pixels</param>
		* <param name="height">Specify the window height in pixels</param>
		* <param name="windowFlags">Specify the desired WindowFlags</param>
		*
		* \note memory allocation and deletion is managed by PXL2D, therefore there is no need to call delete on the window yourself.
		*/
		graphics::Window* CreateWindow(const char* windowHandle, int width, int height, unsigned int windowFlags);

		/*!
		* \brief Creates and returns a new Layer.
		*
		* <param name="depth">Specify the layer depth (Value is clamped between -1.0 - 1.0</param>
		*
		* \note memory allocation and deletion is managed by PXL2D, therefore there is no need to call delete on the layer.
		*/
		Layer* CreateLayer(const math::Matrix4x4& view, graphics::Shader* shader, float depth = 0.0f);

		/*!
		* \brief Runs once upon initialization
		*
		* Allows the game to perform any initialization it needs to before starting to run.
		*/
		virtual void Init() = 0;
		/*!
		* \brief Runs once every frame
		*
		* Allows the game to run logic such as updating the world,
		* checking for collisions, gathering input, and playing audio.
		* <param name="deltaTime">The time in milliseconds it took to complete the last frame.</param>
		*/
		virtual void Update(float deltaTime) = 0;

	private:
		void run();

	private:
		std::vector<std::pair<float,Layer*>> m_layers;
		graphics::Window*		m_window;
		Time*					m_time;
		input::KeyboardInput*   m_input;
		audio::Audio*			m_audio;
		physics::Physics*		m_physics;
	};
}