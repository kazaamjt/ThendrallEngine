#pragma once

#include <string>

#include "GLTexture.hpp"

namespace Engine::TextureLoader {

GLTexture load_png(const std::string &name);

} // Engine::TextureLoader
