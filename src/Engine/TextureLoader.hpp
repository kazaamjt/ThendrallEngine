#pragma once

#include <string>

#include "GLTexture.hpp"

namespace Engine {

class TextureLoader {
public:
	static GLTexture load_png(const std::string &name);
};
} // Engine
