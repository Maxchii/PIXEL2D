#pragma once
#include "..//Core/ValueTypes.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

struct GLFWwindow;
namespace PIXL { class PIXL2D; }

namespace PIXL{ namespace graphics {

	/*!
	* \brief Window flags
	*
	* Ads the specified window flags such as FULLSCREEN mode, BORDERLESS or RESIZABLE to the window initialization. 
	*/
	enum WindowFlags
	{
		FULLSCREEN  = 0x1,
		BORDERLESS  = 0x2,
		RESIZABLE   = 0x4,
	};

	class Window final
	{
		friend class PIXL2D;
	public:
		Window(const std::string& windowHandle, int width, int height, UInt32 windowFlags = 0);
		~Window();

		bool Closed() const;
		inline int Width() const { return m_width; }
		inline int Height() const { return m_height; }
		void EnableVsync(bool state);
		void SetWindowName(const std::string& newName);
		void SetWindowFlags(unsigned int windowFlags);

	private:
		bool Init();
		void Clear() const;
		void Update();
		
		//friend void window_frame_buffer_size(GLFWwindow* window, int width, int height);
		//TODO Add a way to update the m_width, m_height variables when the window is resized

	private:
		static GLFWwindow* m_window;
		int m_width;
		int m_height;
		std::string m_windowHandle;
		UInt32 m_windowFlags;

	};

} }