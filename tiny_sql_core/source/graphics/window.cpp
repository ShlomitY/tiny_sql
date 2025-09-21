#include "window.h"

namespace tiny { namespace graphics {
	void window_resize(GLFWwindow* window, int width, int height);
	
	Window::Window(const char* title, int height, int width) {
		m_title = title;
		m_height = height;
		m_width = width;
		//m_closed = false;
		if (!init()) {
			glfwTerminate();
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
		glfwSetWindowSizeCallback(m_window, window_resize);


		if (glewInit() != GLEW_OK) {
			std::cout << "couldnt initialize glew";
			return false;

		}
		return true;
	}

	void window_resize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}


}
}