#include "Game.hpp"

#include <GL/glew.h>

#include "Terminal.hpp"

Game::Game(const std::string &_name):
	name(_name),
	window(nullptr),
	screen_width(1024),
	screen_height(768),
	state(GameState::INIT)
{
	Terminal::out_debug("Setting up game class for " + name);
}

void Game::init() {
	Terminal::out_debug("Initilazing SDL");
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		Terminal::out_error("Failed to initialize SDL");
		exit(1);
	}

	Terminal::out_debug("Initilazing SDL window");
	window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
		SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL),
		SDL_DestroyWindow
	);

	if (!window)
	{
		Terminal::out_error("Failed to initialize SDL window");
		Terminal::out_error(SDL_GetError());
		exit(1);
	}

	Terminal::out_debug("Creating GL context");
	SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
	if (!gl_context)
	{
		Terminal::out_error("Failed to initialize GL context");
		exit(1);
	}

	glewExperimental = GL_TRUE;
	Terminal::out_debug("Initilazing GL");
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		Terminal::out_warning("Failed to initialize GL context");
		std::cout << "GLEW error: " << error << std::endl;
		std::cout << "OpenGL error " << glGetError() << std::endl;
		exit(1);
	}
}

void Game::run() {
	init();
	state = GameState::RUN;
}

Game::~Game() {
	Terminal::out_debug("Cleaning up game class for " + name);
}
