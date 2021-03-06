#pragma once
#include <iostream>
#include <string>

namespace Engine {

class Terminal {
public:
	static void enable_debug();
	static void toggle_debug();

	static void out_debug(const std::string &msg);
	static void out_info(const std::string &msg);
	static void out_warning(const std::string &msg);
	static void out_error(const std::string &msg, bool exit=true);

	[[ noreturn ]] static void freeze_exit();

private:
	static bool debug;

};

} // Engine
