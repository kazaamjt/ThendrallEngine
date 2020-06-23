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
		Terminal::wait_for_input();
		exit(1);
	}

	Terminal::out_debug("Initilazing SDL window");
	window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
		SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL),
		SDL_DestroyWindow
	);

	if (!window) {
		Terminal::out_error("Failed to initialize SDL window");
		Terminal::out_error(SDL_GetError());
		Terminal::wait_for_input();
		exit(1);
	}

	Terminal::out_debug("Creating OpenGL context");
	SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
	if (!gl_context) {
		Terminal::out_error("Failed to initialize OpenGL context");
		Terminal::wait_for_input();
		exit(1);
	}

	glewExperimental = GL_TRUE;
	Terminal::out_debug("Initilazing GL");
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Terminal::out_error("Failed to initialize GL context");
		std::cout << "GLEW error: " << error << std::endl;
		std::cout << "OpenGL error: " << glGetError() << std::endl;
		Terminal::wait_for_input();
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, screen_width, screen_height);
}

void Game::run() {
	init();
	main_loop();
}

void Game::main_loop() {
	state = GameState::RUN;
	while (state != GameState::STOP) {
		process_input();
		draw();
	}
}

void Game::process_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				state = GameState::STOP;
			} break;

			default: {
				// Terminal::out_debug("Unhandled event");
			} break;
		}
	}
}

void Game::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window.get());
}

Game::~Game() {
	Terminal::out_debug("Cleaning up game class for " + name);
}
