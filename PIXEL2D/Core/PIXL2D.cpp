#include "PIXL2D.h"
#include "..//Debugging/Debug.h"
#include <algorithm>

namespace PIXL
{
	void PIXL2D::Start()
	{
		m_time = new Time();
		m_time->Init();
		m_audio = new audio::Audio();
		m_audio->Init();
		m_physics = new physics::Physics();
		m_physics->Init(math::Vector2f(0, -9.81));
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

	auto CompareLayerDepth = [](std::pair<float, Layer*> const& a, std::pair<float, Layer*> const& b)
	{
		return a.first < b.first;
	};

	Layer* PIXL2D::CreateLayer(const math::Matrix4x4& view, graphics::Shader* shader, float depth /*= 0.0f*/)
	{	
		if (depth > 1)
			depth = 1.0f;
		else if (depth < -1)
			depth = -1.0f;

		Layer* layer = new Layer(new graphics::SpriteBatch(), shader, view);
		m_layers.push_back(std::pair<float,Layer*>(depth,layer));

		
		std::sort(m_layers.begin(), m_layers.end(), CompareLayerDepth);


		return layer;
	}

	void PIXL2D::run()
	{
		
		while (!m_window->Closed())
		{
			m_time->Step();
			m_window->Clear();
			
			Update(m_time->m_deltaTime);
			for (int i = 0; i < m_layers.size(); i++){
				m_layers[i].second->Refresh();
				m_layers[i].second->Update(m_time->m_deltaTime);
			}

			m_input->Update();
			if (m_time->m_frames < 50)
			{
				m_physics->Update(0.02f);
			}
			for (int i = 0; i < m_layers.size();i++)
				m_layers[i].second->Draw();

			m_audio->Update();
			m_window->Update();
		}
	}

	PIXL2D::~PIXL2D()
	{
		for (int i = 0; i < m_layers.size() ; i++)
		{
			delete m_layers[i].second;
		}
		m_layers.clear();
		delete m_window;
	}

	

}