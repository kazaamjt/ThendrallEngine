#pragma once
#include <memory>
#include <string>
#include <vector>

namespace Engine {

class IOManager {
public:
	static std::unique_ptr<std::vector<char>> read_file_to_buffer(const std::string &file_path);

private:

};
} // Engine
