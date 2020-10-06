#include "ResourceManager.hpp"

namespace Engine {

ResourceManager::ResourceManager():
	texture_cache() {
	
}

ResourceManager::~ResourceManager() {
	
}

GLTexture ResourceManager::get_texture(const std::string &name) {
	return texture_cache.get_texture(name);
}

} // Engine
