#include "PIXL2D.h"
#include "..//Debugging/Debug.h"

namespace PIXL
{
	void PIXL2D::Start()
	{
		m_time = new Time();
		m_time->Init();
		m_audio = new audio::Audio();
		m_audio->Init();

		Init();
		m_input = new input::KeyboardInput();
		m_input->Init(m_window->m_window);
	
		run();
	}

	graphics::Window* PIXL2D::CreateWindow(const char*windowHandle, int width, int height, unsigned int windowFlags)
	{
		m_window = new graphics::Window(windowHandle, width, height, windowFlags);
		return m_window;
	}

	void PIXL2D::run()
	{
		while (!m_window->Closed())
		{
			m_time->Step();
			m_window->Clear();
			m_input->Update();
			Update(m_time->m_deltaTime);
			Render();
			m_audio->Update();
			m_window->Update();

			/*string fpsString = std::to_string(Time::Instance().GetFps());
			fpsString.append(" FPS");
			m_window->SetWindowName(fpsString);*/
		}
	}

	PIXL2D::~PIXL2D()
	{
		delete m_window;
	}
}