#pragma once
#include <iostream>
#include <string>

class Terminal {
public:
	static void enable_debug();
	static void toggle_debug();

	static void out_debug(const std::string &msg);
	static void out_info(const std::string &msg);
	static void out_warning(const std::string &msg);
	static void out_error(const std::string &msg);

private:
	static bool debug;
};
