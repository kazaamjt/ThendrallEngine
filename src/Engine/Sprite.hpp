#pragma once
#include <string>
#include <memory>

#include <GL/glew.h>

#include "GLTexture.hpp"
#include "Context.hpp"

namespace Engine {

class Sprite {
public:
	Sprite(
		float x, float y,
		float width, float height,
		const std::string& texture_names,
		std::shared_ptr<Context> context
	);
	~Sprite();

	void update(float x, float y);
	void draw();

private:
	float x;
	float y;
	float width;
	float height;
	GLuint vbo_id;
	std::string texture_name;
	std::shared_ptr<Context> context;
	GLTexture texture;
};
} // Engine
