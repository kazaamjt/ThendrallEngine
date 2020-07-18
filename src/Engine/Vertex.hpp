#pragma once
#include <GL\glew.h>

namespace Engine {

struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte red;
	GLubyte green;
	GLubyte blue;
	GLubyte alpha;
};

struct Vertex {
	Position position;
	Color color;
};
} // Engine
