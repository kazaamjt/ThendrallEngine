#include <iostream>

#include <cxxopts.hpp>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "terminal.hpp"

inline void init_options(int argc, char *argv[]) {
	cxxopts::Options options("Thendrall Tales", "Thendrall Tales v0.0.1");
	options.add_options()("d,debug", "Enable debugging");

	auto result = options.parse(argc, argv);
	if (result.count("debug")) {
		Terminal::enable_debug();
		Terminal::out_debug("Enabeling debug output");
	}
}

int main(int argc, char *argv[]) {
	Terminal::out_info("Starting up Thendrall Tales");
	init_options(argc, argv);

	SDL_Init(SDL_INIT_EVERYTHING);

	return 0;
}
