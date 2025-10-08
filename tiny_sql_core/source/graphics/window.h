#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace tiny{ namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
	class Window {

		private:
			friend struct GLFWwindow;
			const char* m_title;
			int m_width, m_height;
			GLFWwindow* m_window;
			bool m_closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double mx, my;
		public:
			Window(const char* title, int width, int height);
			virtual ~Window();
			bool closed() const;
			void update();
			void clear() const;

			int getWidth() const { return m_width; }
			int getHeight() const { return m_height; }

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int keycode) const;
			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			
	};
	
	
}
}
