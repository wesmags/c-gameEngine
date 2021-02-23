

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"



int main() {

	using namespace rosy;
	using namespace graphics;
	using namespace maths;
	
	Window window("Rosy!", 800, 600);
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);


	
	GLfloat vertices[] =
	{
		4, 3, 0,
		12, 3, 0,
		4, 6, 0,
		4, 6, 0,
		12, 6, 0,
		12, 3, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("m1_matrix", mat4::translation(vec3(100, 100, 100))); 

	/*mat4 position = mat4::translation(vec3(2, 3, 4));
	position *= mat4::identity(); */



	float lightx = 8.0f;
	float lighty = 4.5f;
	shader.setUniform2f("light_pos", vec2(8.0f, 4.5f));
	shader.setUniform4f("colour", vec4(0.6f, 0.9f, 0.9f, 1.0f));
	

	while (!window.closed()) {
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}