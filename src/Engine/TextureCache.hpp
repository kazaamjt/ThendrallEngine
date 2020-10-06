#pragma once
#include <string>
#include <map>

#include "GLTexture.hpp"

namespace Engine {

class TextureCache {
public:
	TextureCache();
	~TextureCache();

	GLTexture get_texture(const std::string &name);

private:
	std::map<std::string, GLTexture> texture_map;

};
} // Engine
