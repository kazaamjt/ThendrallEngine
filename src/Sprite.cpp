#include "Sprite.hpp"
#include "Terminal.hpp"

Sprite::Sprite(float _x, float _y, float _width, float _height):
	x(_x), y(_y), width(_width), height(_height), vbo_id(0)
{
	
}

void Sprite::update(float _x, float _y) {
	x = _x;
	y = _y;

	if (vbo_id == 0) {
		glGenBuffers(1, &vbo_id);
	}

	float vertex_data[12];
	// Triangle 1
	vertex_data[0] = x + width;
	vertex_data[1] = y + height;

	vertex_data[2] = x ;
	vertex_data[3] = y + height;

	vertex_data[4] = x;
	vertex_data[5] = y;

	// Triangle 2
	vertex_data[6] = x;
	vertex_data[7] = y;

	vertex_data[8] = x + width;
	vertex_data[9] = y;

	vertex_data[10] = x + width;
	vertex_data[11] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite() {
	if (vbo_id != 0) {
		glDeleteBuffers(1, &vbo_id);
	}
}
