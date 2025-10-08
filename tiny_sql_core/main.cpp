
#include "./source/graphics/window.h"

#include <vector>
#include <cmath>

void generateO(float centerX, float centerY, float rx, float ry, int segments, std::vector<float>& vertices) {
	float angleStep = 2.0f * 3.14 / segments;
	for (int i = 0; i < segments; ++i) {
		float theta1 = i * angleStep;
		float theta2 = (i + 1) * angleStep;

		float x1 = centerX + rx * cos(theta1);
		float y1 = centerY + ry * sin(theta1);
		float x2 = centerX + rx * cos(theta2);
		float y2 = centerY + ry * sin(theta2);

		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(x2);
		vertices.push_back(y2);
	}
}

void generateC(float centerX, float centerY, float rx, float ry, int segments, std::vector<float>& vertices) {
	// Define arc from 45° to 315° (leaving the right side open)
	float startAngle = 3.14 / 4;          // 45°
	float endAngle = 3.14 * 7.0f / 4.0f; // 315°
	float angleStep = (endAngle - startAngle) / segments;

	for (int i = 0; i < segments; ++i) {
		float theta1 = startAngle + i * angleStep;
		float theta2 = startAngle + (i + 1) * angleStep;

		float x1 = centerX + rx * cos(theta1);
		float y1 = centerY + ry * sin(theta1);
		float x2 = centerX + rx * cos(theta2);
		float y2 = centerY + ry * sin(theta2);

		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(x2);
		vertices.push_back(y2);
	}
}



int main() {
	
	using namespace tiny::graphics;


	std::vector<float> lettersVertices;

	lettersVertices.insert(lettersVertices.end(),{
		// Letter E
		-0.9f, 0.7f,  // Left vertical top
		-0.9f, 0.6f,  // Left vertical bottom

		-0.9f, 0.7f,  // Left vertical top
		-0.85f, 0.7f,  // Right vertical top

		-0.9f, 0.6f,  // Left vertical bottom
		-0.85f, 0.6f,  // Right vertical bottom

		-0.9f, 0.65f,  // Horizontal middle left
		-0.85f, 0.65f,  // Horizontal middle right


		// Letter N
		-0.825f, 0.7f,  // Left vertical top
		-0.825f, 0.6f,  // Left vertical bottom

		-0.775f, 0.7f,  // Right vertical top
		-0.775f, 0.6f,  // Right vertical bottom

		-0.825f, 0.7f,  // Left vertical top
		-0.775f, 0.6f,  // Right vertical bottom

		// Letter T	
		-0.75f, 0.7f,  // Left vertical top
		-0.7f, 0.7f,  // right vertical top

		-0.725f, 0.7f,  // Right vertical top
		-0.725f, 0.6f,  // Right vertical bottom

		// Letter E
		-0.675f, 0.7f,  // Left vertical top
		-0.675f, 0.6f,  // Left vertical bottom

		-0.675f, 0.7f,  // Left vertical top
		-0.625f, 0.7f,  // Right vertical top

		-0.675f, 0.6f,  // Left vertical bottom
		-0.625f, 0.6f,  // Right vertical bottom

		-0.675f, 0.65f,  // Horizontal middle left
		-0.625f, 0.65f,  // Horizontal middle right

		// Letter R

		//normal left line
		-0.6f, 0.7f,  // Left vertical top
		-0.6f, 0.6f,  // Left vertical bottom

		//top horizontal line
		-0.5625f, 0.7f,  // Left vertical top
		-0.6f, 0.7f,  // Right vertical top

		//top alachson
		-0.5625f, 0.7f,  // left top
		-0.55f, 0.68f,  // Right botton

		-0.55f, 0.68f,  // Right vertical top
		-0.55f, 0.65f,  // right vertical bottom

		//bottom alachson
		-0.55f, 0.65f,  // right top
		-0.5625f, 0.63f,  // Right botton

		//bottom horizontal line
		-0.6f, 0.63f,  // Left vertical 
		-0.5625f, 0.63f,  // Right vertical 

		//diagonal line
		-0.55f, 0.6f,  // right vertical
		-0.575f, 0.63f,  // left vertical

		/////////////////////space////////////

		//letter Y
		-0.5f, 0.7f,  // Left vertical top
		-0.475f, 0.65f,  // right vertical

		-0.475f, 0.65f,  // Left vertical top
		-0.45f, 0.7f,  // right vertical

		-0.475f, 0.65f,  // middle top
		-0.475f, 0.6f  // middle bottom
	});
	generateO(-0.415f, 0.65f, 0.025f, 0.05f, 36, lettersVertices);

	lettersVertices.insert(lettersVertices.end(), {
		// Letter U
		-0.375f, 0.7f,  
		-0.375f, 0.62f,

		-0.375f, 0.62f,
		-0.365f, 0.6f,

		-0.365f, 0.6f,
		-0.335f, 0.6f, 

		-0.325f, 0.62f,
		-0.335f, 0.6f,

		-0.325f, 0.62f, 
		-0.325f, 0.7f, 

		// Letter R

		//normal left line
		-0.3f, 0.7f,  // Left vertical top
		-0.3f, 0.6f,  // Left vertical bottom

		//top horizontal line
		-0.2625f, 0.7f,  // Left vertical top
		-0.3f, 0.7f,  // Right vertical top

		//top alachson
		-0.2625f, 0.7f,  // left top
		-0.25f, 0.68f,  // Right botton

		-0.25f, 0.68f,  // Right vertical top
		-0.25f, 0.65f,  // right vertical bottom

		//bottom alachson
		-0.25f, 0.65f,  // right top
		-0.2625f, 0.63f,  // Right botton

		//bottom horizontal line
		-0.3f, 0.63f,  // Left vertical 
		-0.2625f, 0.63f,  // Right vertical 

		//diagonal line
		-0.25f, 0.6f,  // right vertical
		-0.275f, 0.63f,  // left vertical


	});


	generateC(-0.175f, 0.65f, 0.025f, 0.05f, 24, lettersVertices);
	generateO(-0.125f, 0.65f, 0.025f, 0.05f, 36, lettersVertices);
	lettersVertices.insert(lettersVertices.end(), {
		// Letter M
		-0.085f, 0.7f,
		-0.085f, 0.6f,

		-0.035f, 0.7f,
		-0.035f, 0.6f,

		-0.06f, 0.65f,
		-0.085f, 0.7f,

		-0.035f, 0.7f,
		-0.06f, 0.65f,

		// Letter M
		-0.01f, 0.7f,
		-0.01f, 0.6f,

		0.04f, 0.7f,
		0.04f, 0.6f,

		0.015f, 0.65f,
		-0.01f, 0.7f,

		0.04f, 0.7f,
		0.015f, 0.65f,

		// Letter A
		0.065f, 0.6f,
		0.09f, 0.7f,

		0.09f, 0.7f,
		0.115f, 0.6f,

		0.075f, 0.64f,
		0.105f, 0.64f,


		// Letter N
		0.14f, 0.7f,  // Left vertical top
		0.14f, 0.6f,  // Left vertical bottom

		0.19f, 0.7f,  // Right vertical top
		0.19f, 0.6f,  // Right vertical bottom

		0.14f, 0.7f,  // Left vertical top
		0.19f, 0.6f,  // Right vertical bottom

		//letter D

		0.215f, 0.7f,  // Left vertical top	
		0.215f, 0.6f,  // Left vertical bottom

		0.215f, 0.7f,  
		0.235f, 0.7f,

		0.235f, 0.7f,
		0.255f, 0.695f,

		0.255f, 0.695f,
		0.265f, 0.68f,

		0.265f, 0.68f,	
		0.265f, 0.62f,

		0.265f, 0.62f,
		0.255f, 0.605f,

		0.255f, 0.605f,
		0.235f, 0.6f,

		0.215f, 0.6f,
		0.235f, 0.6f,

	});

	generateO(0.28f, 0.63f, 0.005f, 0.005f, 120, lettersVertices);
	generateO(0.28f, 0.67f, 0.005f, 0.005f, 120, lettersVertices);


	Window window("Tiny SQL", 400, 500);
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (!window.closed()) {
		window.clear();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lettersVertices.data());
		glDrawArrays(GL_LINES, 0, lettersVertices.size() / 2);
		glDisableClientState(GL_VERTEX_ARRAY);

		glBegin(GL_QUADS);
		glVertex2f(-0.9f, 0.5f);
		glVertex2f(0.3f, 0.5f);
		glVertex2f(0.3f, 0.3f);
		glVertex2f(-0.9f, 0.3f);
		glEnd();
		window.update();
	}

	return 0;
}