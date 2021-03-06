#include "window.hpp"

namespace evo {
namespace graphics {

	Window::Window(const char *title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height) {

		if (!init()) glfwTerminate();

		Font::init();
		audio::SoundManager::init();
		Debug::CheckError();

		for (int i = 0; i < MAX_KEYS; i++) {
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
	}

	Window::~Window() {
		glfwTerminate();
	}

	bool Window::init() {
		if (!glfwInit()) {
			Debug::Log("Failed to initialize GLFW!", LogType::Error);
			return false;
		}
		//create OpenGL 3.0+ context
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MacOS
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		if(!m_Window) {
			Debug::Log("Failed to create GLFW window!", LogType::Error);
			return false;
		}
		glfwMakeContextCurrent(m_Window);

		//must be called BEFORE calling glewInit();
		glewExperimental = true; // DO NOT DELETE!

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0.0);

		if (glewInit() != GLEW_OK) {
			Debug::Log("Could not initialize GLEW!", LogType::Error);
			return false;
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::string errmsg = "OpenGL Version: " + std::string((char*)glGetString(GL_VERSION));
		Debug::Log(errmsg, LogType::Note);

		std::cerr << glfwGetVersionString() << std::endl;

		checkJoystick();
		if(m_Joystick) std::cerr << "Buttoncount: " << m_JoystickButtonsCount << std::endl;

		return true;
	}


	bool Window::isJoystickButtonPressed(unsigned int button) const {
		if(m_Joystick && m_JoystickButtonsCount > button && m_JoystickButtons[button] == GLFW_PRESS) return true;
		return false;
	}

	float Window::getJoystickAxis(unsigned int axis) const {
		if(m_Joystick && m_JoystickAxesCount > axis) return m_JoystickAxes[axis];
		//Debug::Log("Joystick Axis count wrong", LogType::Error);
		return 0;
	}

	bool Window::isKeyPressed(unsigned int keycode) const {
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}

	bool Window::isKeyTyped(unsigned int keycode) const {
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_KeyTyped[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const {
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	bool Window::isMouseButtonClicked(unsigned int button) const {
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseClicked[button];
	}

	void Window::getMousePosition(double& x, double& y) const {
		x = mx;
		y = my;
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

 	void Window::update() {
		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			Debug::CheckError();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		BatchRenderer2D::setWindowSize(maths::vec2((float)m_Width,(float)m_Height));
		audio::SoundManager::update();
		checkJoystick();
		Debug::CheckError();
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Window::window_resize(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void Window::checkJoystick() {
		if(glfwJoystickPresent(GLFW_JOYSTICK_1)){
			m_Joystick = true;
			m_JoystickButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &m_JoystickButtonsCount);
			m_JoystickAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &m_JoystickAxesCount);
			return;
		}
		m_Joystick = false;
	}

	void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}

} }
