#include "IOManager.hpp"

#include <fstream>

#include "Terminal.hpp"

namespace Engine {

std::unique_ptr<std::vector<char>> IOManager::read_file_to_buffer(const std::string &file_path) {
	auto buffer = std::unique_ptr<std::vector<char>>(new std::vector<char>());
	std::ifstream file(file_path, std::ios::binary);
	if (file.fail()) {
		throw "Failed to load file " + file_path + ": " + strerror(errno);
	}

	file.seekg(0, std::ios::end);
	long long file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	// Reduce filesize by header size
	file_size -= file.tellg();

	buffer->resize(static_cast<unsigned long long>(file_size));
	file.read(&buffer->at(0), file_size);
	file.close();

	return std::move(buffer);
}

} // Engine
