#include "KeyboardInput.h"
#include "..//Debugging/Debug.h"
#include "..//Core/ValueTypes.h"
#include "..//Math/Vector2.h"
#include "..//Graphics/Window.h"

namespace PIXL { namespace input {

	GLFWwindow* KeyboardInput::m_window;
	Float64 KeyboardInput::m_scrollWheelY;
	Float64 KeyboardInput::m_scrollWheelX;
	Float64 KeyboardInput::m_mouseY;
	Float64 KeyboardInput::m_mouseX;

	bool KeyboardInput::m_mouseButtonsPressedCache[MAX_BUTTONS];
	bool KeyboardInput::m_mouseButtonsState[MAX_BUTTONS];
	bool KeyboardInput::m_mouseButtons[MAX_BUTTONS];
	bool KeyboardInput::m_keysPressedCache[MAX_KEYS];
	bool KeyboardInput::m_keyState[MAX_KEYS];
	bool KeyboardInput::m_keys[MAX_KEYS];

	void KeyboardInput::Init(GLFWwindow* window)
	{
		m_window = window;
		glfwSetWindowUserPointer(m_window, this);


		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_keys[i] = false;
			m_keyState[i] = false;
			m_keysPressedCache[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_mouseButtons[i] = false;
			m_mouseButtonsState[i] = false;
			m_mouseButtonsPressedCache[i] = false;
		}


		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, mouse_position_callback);
		glfwSetScrollCallback(m_window, mouse_scroll_callback);
	}

	void KeyboardInput::Update()
	{
		for (int i = 0; i < MAX_KEYS; i++)
			m_keysPressedCache[i] = m_keys[i] && !m_keyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_mouseButtonsPressedCache[i] = m_mouseButtons[i] && !m_mouseButtonsState[i];

		memcpy(m_keyState, m_keys, MAX_KEYS);
		memcpy(m_mouseButtonsState, m_mouseButtons, MAX_BUTTONS);
	}

	bool KeyboardInput::GetKey(UInt32 keycode)
	{
		if (keycode >= MAX_KEYS){
			string errorString = "Keycode [";
			errorString.append(std::to_string(keycode));
			errorString.append("] is out of range");

			debugging::Debug::LogError(nullptr, errorString.c_str());
			return false;
		}
		return m_keys[keycode];
	}
	bool KeyboardInput::GetKeyDown(UInt32 keycode)
	{
		if( keycode >= MAX_KEYS){
			string errorString = "Keycode [";
			errorString.append(std::to_string(keycode));
			errorString.append("] is out of range");

			debugging::Debug::LogError(nullptr, errorString.c_str());
			return false;
		}

		if (!m_keyState[keycode] && m_keys[keycode]) {
			m_keysPressedCache[keycode] = true;
			return m_keys[keycode];
		}
		else
			return false;
	}
	bool KeyboardInput::GetKeyUp(UInt32 keycode)
	{
		if (keycode >= MAX_KEYS){
			string errorString = "Keycode [";
			errorString.append(std::to_string(keycode));
			errorString.append("] is out of range");

			debugging::Debug::LogError(nullptr, errorString.c_str());
			return false;
		}

		return m_keyState[keycode] && !m_keys[keycode];
	}
	bool KeyboardInput::GetMouseButton(UInt32 button)
	{
		if (button >= MAX_BUTTONS){
			string errorString = "Mouse Button [";
			errorString.append(std::to_string(button));
			errorString.append("] is out of range");

			debugging::Debug::LogError(nullptr, errorString.c_str());
			return false;
		}
		return m_mouseButtonsState[button];
	}
	bool KeyboardInput::GetMouseButtonDown(UInt32 button)
	{
		if (button >= MAX_BUTTONS){
			string errorString = "Mouse Button [";
			errorString.append(std::to_string(button));
			errorString.append("] is out of range");

			debugging::Debug::LogError(nullptr, errorString.c_str());
			return false;
		}
		return m_mouseButtonsPressedCache[button];
	}
	bool KeyboardInput::GetMouseButtonUp(UInt32 button)
	{
		if (button >= MAX_BUTTONS){
			string errorString = "Mouse Button [";
			errorString.append(std::to_string(button));
			errorString.append("] is out of range");

			debugging::Debug::LogError(nullptr, errorString.c_str());
			return false;
		}

		return m_mouseButtonsState[button] && !m_mouseButtons[button];
	}
	math::Vector2 KeyboardInput::getMousePosition()
	{
		return math::Vector2((Float32)m_mouseX, (Float32)m_mouseY);
	}
	PIXL::Float32 KeyboardInput::getMouseScroll()
	{
		return (Float32)m_scrollWheelY;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyboardInput* win = (KeyboardInput*)glfwGetWindowUserPointer(window);
		win->m_keys[key] = action != GLFW_RELEASE;
	}
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		KeyboardInput* win = (KeyboardInput*)glfwGetWindowUserPointer(window);
		win->m_mouseButtons[button] = action != GLFW_RELEASE;
	}
	void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		KeyboardInput* win = (KeyboardInput*)glfwGetWindowUserPointer(window);
		win->m_mouseX = xpos;
		win->m_mouseY = ypos;
	}
	void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		KeyboardInput* win = (KeyboardInput*)glfwGetWindowUserPointer(window);
		win->m_scrollWheelX = xoffset;
		win->m_scrollWheelY = yoffset;
	}

}
}