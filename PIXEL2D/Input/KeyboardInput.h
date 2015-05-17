#pragma once
#include "..//Core/ValueTypes.h"

struct GLFWwindow;
namespace PIXL{ class PIXL2D; }
namespace PIXL{ namespace math{ class Vector2; } }
namespace PIXL{ namespace graphics{ class Window; } }


namespace PIXL { namespace input {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

	class KeyboardInput final
	{
		friend class PIXL2D;
	public:
		static bool GetKey(UInt32 keycode);
		static bool GetKeyDown(UInt32 keycode);
		static bool GetKeyUp(UInt32 keycode);
		static bool GetMouseButton(UInt32 button);
		static bool GetMouseButtonDown(UInt32 button);
		static bool GetMouseButtonUp(UInt32 button);
		static math::Vector2 getMousePosition();
		static Float32 getMouseScroll();
	private:
		KeyboardInput(){}
		~KeyboardInput(){}

		void Init(GLFWwindow* window);
		void Update();

		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		static GLFWwindow* m_window;
		static bool	m_keys[MAX_KEYS];
		static bool	m_keyState[MAX_KEYS];
		static bool	m_keysPressedCache[MAX_KEYS];
		static bool	m_mouseButtons[MAX_BUTTONS];
		static bool	m_mouseButtonsState[MAX_BUTTONS];
		static bool	m_mouseButtonsPressedCache[MAX_BUTTONS];
		static Float64	m_mouseX;
		static Float64	m_mouseY;
		static Float64	m_scrollWheelX;
		static Float64	m_scrollWheelY;
	};

} }