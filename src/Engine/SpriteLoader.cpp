#include "SpriteLoader.hpp"

#include <memory>
#include <vector>

#include <picopng.hpp>

#include "IOManager.hpp"
#include "Terminal.hpp"

namespace Engine {

GLTexture SpriteLoader::load_png(const std::string &name) {
	GLTexture texture = {};

	std::unique_ptr<std::vector<unsigned char>> raw_data;
	std::vector<unsigned char> out;

	try {
		raw_data = IOManager::read_file_to_buffer("data/textures/" + name + ".png");
	} catch(const std::exception& e) {
		Terminal::out_error(e.what());
	}

	unsigned long width, height;
	int error_code = decodePNG(out, width, height, &raw_data->at(0), raw_data->size());
	if (error_code != 0) {
		Terminal::out_error("PicoPNG: failed to decode png (ErrorCode " + std::to_string(error_code) + ")");
	}
	texture.width = static_cast<int>(width);
	texture.height = static_cast<int>(height);

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(texture.id, 0);
	return texture;
}

} // Engine
