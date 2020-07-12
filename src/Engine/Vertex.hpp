#pragma once
#include <GL\glew.h>

namespace Engine {

struct Vertex {
	struct Position {
		float x;
		float y;
	} position;

	struct Color {
		GLubyte red;
		GLubyte green;
		GLubyte blue;
		GLubyte alpha;
	} color;
};
} // Engine
