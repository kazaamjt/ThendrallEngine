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
	vertex_data[0].set_position(x + width, y + height);
	vertex_data[0].set_uv(1.0f, 1.0f);

	vertex_data[1].set_position(x, y + height);
	vertex_data[1].set_uv(0.0f, 1.0f);

	vertex_data[2].set_position(x, y);
	vertex_data[2].set_uv(0.0f, 0.0f);

	// Triangle 2
	vertex_data[3].set_position(x, y);
	vertex_data[3].set_uv(0.0f, 0.0f);

	vertex_data[4].set_position(x + width, y);
	vertex_data[4].set_uv(1.0f, 0.0f);

	vertex_data[5].set_position(x + width, y + height);
	vertex_data[5].set_uv(1.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		vertex_data[i].set_color( 255, 255, 255, 255);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

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

	// uv attribute
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_TRUE,
		sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, uv))
	);

	// Draw the 6 vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite() {
	if (vbo_id != 0) {
		glDeleteBuffers(1, &vbo_id);
	}
}

} // Engine
