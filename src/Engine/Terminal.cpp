#include "Terminal.hpp"
#include <rang.hpp>

namespace Engine {

bool Terminal::debug = false;

void Terminal::enable_debug() {
	debug = true;
}

void Terminal::toggle_debug() {
	if (debug) {
		debug = false;
	} else {
		debug = true;
	}
}

void Terminal::out_debug(const std::string &msg) {
	if (debug) {
		std::cout << "[" << rang::fg::blue << "DEBUG" << rang::fg::reset << "] " << msg << std::endl;
	}
}

void Terminal::out_info(const std::string &msg) {
	std::cout << "[" << rang::fg::green << "INFO" << rang::fg::reset << "] " << msg << std::endl;
}

void Terminal::out_warning(const std::string &msg) {
	std::cerr << "[" << rang::fg::yellow << "WARNING" << rang::fg::reset << "] " << msg << std::endl;
}

void Terminal::out_error(const std::string &msg, bool exit) {
	std::cerr << "[" << rang::fg::red << "ERROR" << rang::fg::reset << "] " << msg << std::endl;
	if (exit) freeze_exit();
}

void Terminal::freeze_exit() {
	std::cout << "\nPress Enter to continue..." << std::endl;
	std::cin.ignore();
	exit(1);
}

} // Engine
