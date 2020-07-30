#pragma once

#include <string>

#include "GLTexture.hpp"

namespace Engine {

class SpriteLoader {
public:
	static GLTexture load_png(const std::string &name);
};
} // Engine
