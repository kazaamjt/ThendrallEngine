#include <iostream>

#include <cxxopts.hpp>

#include "Engine/Terminal.hpp"
#include "Engine/Game.hpp"

inline void init_options(int argc, char *argv[]) {
	cxxopts::Options options("Thendrall Tales", "Thendrall Tales v0.0.1");
	options.add_options()("d,debug", "Enable debugging");

	auto result = options.parse(argc, argv);
	if (result.count("debug")) {
		Engine::Terminal::enable_debug();
		Engine::Terminal::out_debug("Enabeling debug output");
	}
}

int main(int argc, char *argv[]) {
	Engine::Terminal::out_info("Starting up Thendrall Engine");
	init_options(argc, argv);

	Engine::Game *game = new Engine::Game("Thendrall Tales");
	game->run();

	return 0;
}
