#include "window.h"

namespace tiny { namespace graphics {
	
	
	void window_resize(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	
	Window::Window(const char* title, int height, int width) {
		m_title = title;
		m_height = height;
		m_width = width;
		//m_closed = false;
		if (!init()) {
			glfwTerminate();
		}

		for(int i = 0; i < MAX_KEYS; i++) {
			m_Keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_MouseButtons[i] = false;
		}
	}

	bool Window::closed() const {

		return glfwWindowShouldClose(m_window) == 1;
	}

	Window::~Window() {
		glfwTerminate();
	}


	void Window::update(){
		glfwPollEvents();
		//glfwGetFramebufferSize(m_window, &m_width, &m_height);
		glfwSwapBuffers(m_window);
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::init() {
		if (!glfwInit()) {
			std::cout << "Error: GLFW initialization failed!" << std::endl;
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
		if (!m_window) {
			std::cout << "failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, window_resize);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);

		//importatnt to start glew only after creating context 

		if (glewInit() != GLEW_OK) {
			std::cout << "couldnt initialize glew";
			return false;

		}




		return true;
	}

	bool Window::isKeyPressed(unsigned int keycode) const {
		if (keycode >= MAX_KEYS)
			return false;
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const {
		if (button >= MAX_BUTTONS)
			return false;
		return m_MouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const {
		x = mx;	
		y = my;
	}

	void window_resize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}


	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}


}
}