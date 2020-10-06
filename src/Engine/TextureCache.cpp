#include "TextureCache.hpp"

#include "TextureLoader.hpp"
#include "Terminal.hpp"

namespace Engine {

TextureCache::TextureCache() {
	
}

TextureCache::~TextureCache() {
	
}

GLTexture TextureCache::get_texture(const std::string &name) {
	auto iterator = texture_map.find(name);

	if (iterator == texture_map.end()) {
		Terminal::out_debug("Texture " + name + " -> not in cache, retrieving from file.");
		// TODO: if texture loading fails, replace it.
		GLTexture texture = TextureLoader::load_png(name);

		texture_map.insert(std::make_pair(name, texture));
		return texture;
	}

	Terminal::out_debug("Texture " + name + " -> in cache.");
	return iterator->second;
}

} // Engine
