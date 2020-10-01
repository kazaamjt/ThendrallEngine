#include "IOManager.hpp"

#include <fstream>

#include "Terminal.hpp"

namespace Engine {

std::unique_ptr<std::vector<unsigned char>> IOManager::read_file_to_buffer(const std::string &file_path) {
	Terminal::out_debug("IOManager: loading file " + file_path);
	auto buffer = std::unique_ptr<std::vector<unsigned char>>(new std::vector<unsigned char>());
	std::ifstream file(file_path, std::ios::binary);
	if (file.fail()) {
		Terminal::out_error("Failed to load texture: \"" + file_path + "\"");
	}

	file.seekg(0, std::ios::end);
	long long file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	// Reduce filesize by header size
	file_size -= file.tellg();

	buffer->resize(static_cast<unsigned long long>(file_size));
	file.read(reinterpret_cast<char*>(&buffer->at(0)), file_size);
	file.close();

	return std::move(buffer);
}

} // Engine
