#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>

#include "font.hpp"
#include "../managers/sound_manager.hpp"
#include "BatchRenderer2D.hpp"
#include "../utils/debug.hpp"

namespace evo {
namespace graphics {

	#define MAX_KEYS	1024
	#define MAX_BUTTONS	32

	class Window {
	private:
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;

		bool m_Joystick;
		int m_JoystickButtonsCount;
		int m_JoystickAxesCount;
		const unsigned char *m_JoystickButtons;
		const float *m_JoystickAxes;
		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		double mx, my;
	public:
		Window(const char *name, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		bool isJoysickPresent() const { return m_Joystick; }
		bool isJoystickButtonPressed(unsigned int button) const;
		float getJoystickAxis(unsigned int axes) const;
		bool isKeyPressed(unsigned int keycode) const;
		bool isKeyTyped(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		bool isMouseButtonClicked(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;

	private:
		bool init();
		void checkJoystick();
		static void window_resize(GLFWwindow* window, int width, int height);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }

#endif /* end of include guard: WINDOW_HPP */
