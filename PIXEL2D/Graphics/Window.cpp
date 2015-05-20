#include "Window.h"
#include "..//Debugging/Debug.h"


namespace PIXL{ namespace graphics {

	int Window::m_height;
	int Window::m_width;

	Window::Window(const std::string& windowHandle, int width, int height, UInt32 windowFlags /*= 0*/)
		: m_windowHandle(windowHandle), m_windowFlags(windowFlags)
	{
		m_width = width;
		m_height = height;

		if (!Init()){
			glfwTerminate();
			debugging::Debug::LogError("Window.cpp", "Fatal Error! GLFW terminated!");
		}
	}


	bool Window::Init()
	{
		if (!glfwInit()){
			debugging::Debug::LogError("Window.cpp", "Failed to initialize GLFW!");
			return false;
		}

		const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
		bool fullscreen = false;
		bool borderless = false;

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		if (m_windowFlags & RESIZABLE)
		{
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		}

		if (m_windowFlags & BORDERLESS)
		{
			m_width = monitor->width;
			m_height = monitor->height;
			glfwWindowHint(GLFW_DECORATED, GL_FALSE);
			m_window = glfwCreateWindow(m_width, m_height, m_windowHandle.c_str(), NULL, NULL);
			glfwSetWindowPos(m_window, 0, 0);
			borderless = true;
		}

		if (!fullscreen && !borderless)
		{
			m_window = glfwCreateWindow(m_width, m_height, m_windowHandle.c_str(), NULL, NULL);
			glfwSetWindowPos(m_window, monitor->width / 2 - m_width / 2, monitor->height / 2 - m_height / 2);
		}

		if (!m_window)
		{
			debugging::Debug::LogError("Window.cpp", "Failed to create GLFW Window!");
			return false;
		}

		glfwMakeContextCurrent(m_window);
		//glfwSetFramebufferSizeCallback(m_window, window_frame_buffer_size);

		if (glewInit() != GLEW_OK)
		{
			debugging::Debug::LogError("Window.cpp", "Failed to initialize GLEW!");
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		/*glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);*/

		return true;
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::Update()
	{
		GLenum error = glGetError();

		while (error != GL_NO_ERROR)
		{
			std::string errorString;

			switch (error) {
			case GL_INVALID_OPERATION:
				errorString = "INVALID_OPERATION";
				break;
			case GL_INVALID_ENUM:
				errorString = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				errorString = "INVALID_VALUE";
				break;
			case GL_OUT_OF_MEMORY:
				errorString = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorString = "INVALID_FRAMEBUFFER_OPERATION";
				break;
			default:
				break;
			}
			std::string fullErrorMessage = "OpenGL Error: ";
			fullErrorMessage.append(errorString.c_str());

			debugging::Debug::LogError(nullptr, fullErrorMessage.c_str());
			error = glGetError();
		}
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	bool Window::Closed() const
	{
		return glfwWindowShouldClose(m_window) == 1;
	}

	void Window::EnableVsync(bool state)
	{
		glfwSwapInterval(state);
	}

	void Window::SetWindowName(const std::string& newName)
	{
		glfwSetWindowTitle(m_window, newName.c_str());
		m_windowHandle = newName;
	}

	void Window::SetWindowFlags(unsigned int windowFlags)
	{
		glfwDestroyWindow(m_window);
		m_windowFlags = windowFlags;
		if (!Init()){
			glfwTerminate();
			debugging::Debug::LogError("Window.cpp", "Fatal Error! GLFW terminated!");
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	GLFWwindow* Window::m_window;

/*
	void window_frame_buffer_size(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_width = width;
		win->m_height = height;
	}*/

}
}