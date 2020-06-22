#include <iostream>

#include <cxxopts.hpp>

#include "Terminal.hpp"
#include "Game.hpp"

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
	Terminal::out_info("Starting up Thendrall Engine");
	init_options(argc, argv);

	Game game = Game("Thendrall Tales");
	game.run();

	return 0;
}
