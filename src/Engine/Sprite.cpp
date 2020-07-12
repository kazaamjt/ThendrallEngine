#include "Sprite.hpp"

#include <cstddef>

#include "Terminal.hpp"
#include "Vertex.hpp"

namespace Engine {

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

	Vertex vertex_data[6];
	// Triangle 1
	vertex_data[0].position.x = x + width;
	vertex_data[0].position.y = y + height;

	vertex_data[1].position.x = x ;
	vertex_data[1].position.y = y + height;

	vertex_data[2].position.x = x;
	vertex_data[2].position.y = y;

	// Triangle 2
	vertex_data[3].position.x = x;
	vertex_data[3].position.y = y;

	vertex_data[4].position.x = x + width;
	vertex_data[4].position.y = y;

	vertex_data[5].position.x = x + width;
	vertex_data[5].position.y = y + height;

	for (int i = 0; i < 6; i++) {
		vertex_data[i].color.red = 255;
		vertex_data[i].color.blue = 255;
		vertex_data[i].color.green = 0;
		vertex_data[i].color.alpha = 255;
	}

	vertex_data[1].color.red = 255;
	vertex_data[1].color.blue = 0;
	vertex_data[1].color.green = 255;
	vertex_data[1].color.alpha = 255;

	vertex_data[4].color.red = 0;
	vertex_data[4].color.blue = 255;
	vertex_data[4].color.green = 255;
	vertex_data[4].color.alpha = 255;

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableVertexAttribArray(0);

	// Position attribute
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, position))
	);

	// color attribute
	glVertexAttribPointer(
		1,
		4,
		GL_UNSIGNED_BYTE,
		GL_TRUE,
		sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, color))
	);

	// Draw the 6 vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite() {
	if (vbo_id != 0) {
		glDeleteBuffers(1, &vbo_id);
	}
}

} // Engine
