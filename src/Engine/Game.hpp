#pragma once
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "Sprite.hpp"
#include "GLSLProgram.hpp"

namespace Engine {

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::steady_clock::time_point TimePoint;

enum class GameState {
	INIT,
	RUN,
	STOP,
};

class Game {
public:
	Game(const std::string &name);
	~Game();

	Uint32 sdl_window_flags = SDL_WINDOW_OPENGL;
	void run();

private:
	std::string name;

	void init();

	void main_loop();
	void process_input();
	void draw();

	std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> window;
	int screen_width;
	int screen_height;
	GameState state;

	Sprite sprite;

	GLSLProgram color_shader;
	float time;
};

} // Engine
