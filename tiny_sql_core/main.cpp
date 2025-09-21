
#include "./source/graphics/window.h"

int main() {
	
	using namespace tiny::graphics;

	Window window("Tiny SQL", 600, 800);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (!window.closed()) {
		window.clear();
		window.update();
	}

	return 0;
}