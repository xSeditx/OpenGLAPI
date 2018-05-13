#include"Mesh.h "
#include"Window.h"
#include"Renderer.h""



Cube::Cube() {
	GLfloat VERTICES[] = {
		0,0,0,
		0,3,0,
		8,3,0,
		8,0,0,
	};
	GLushort INDICES[] = {
		0,1,2,
		2,3,0,
	};


	GLfloat BOX[] = {
		1,  1, 1,
		1, -1, 1,
		-1,  1, 1,
		-1, -1, 1,

		-1,  1,-1,
		-1, -1,-1,
		1,  1,-1,
		1, -1,-1,
	};


	GLushort BOXIBO[] = {
		6,5,7,
		7,8,6,
		6,8,4,
		8,2,4,

		8,7,1,
		1,8,2,
		6,5,3,
		3,4,6,

		1,2,4,
		4,3,1,
		5,3,1,
		7,1,3,
	};

	//VertexBuffer = new Buffer(BOX, 3 * 8, 3);    // Buffer(GLfloat *data,GLsizei count,GLint componentcount);
	//IBuffer = VertexBuffer(BOXIBO, 12);
	//IndexBuffer d;
}