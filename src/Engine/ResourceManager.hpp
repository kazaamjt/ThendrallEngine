#pragma once
#include <string>

#include <GL/glew.h>

#include "GLTexture.hpp"
#include "TextureCache.hpp"

namespace Engine {

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	GLTexture get_texture(const std::string &name);
	GLuint bound_texture;

private:
	TextureCache texture_cache;

};
} // Engine
