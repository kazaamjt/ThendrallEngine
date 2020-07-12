#include "Game.hpp"

#include <GL/glew.h>

#include "Terminal.hpp"

namespace Engine {

Game::Game(const std::string &_name):
	name(_name),
	window(nullptr),
	screen_width(1024),
	screen_height(768),
	state(GameState::INIT),
	sprite(-1.0f, -1.0f, 1.0f, 1.0f)
{
	Terminal::out_debug("Setting up game class for " + name);
}

void Game::init() {
	Terminal::out_debug("Initilazing SDL");
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		Terminal::out_error("Failed to initialize SDL");
		Terminal::freeze_exit();
	}

	Terminal::out_debug("Initilazing SDL window");
	window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
		SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL),
		SDL_DestroyWindow
	);

	if (!window) {
		Terminal::out_error("Failed to initialize SDL window", false);
		Terminal::out_error(SDL_GetError());
		Terminal::freeze_exit();
	}

	Terminal::out_debug("Creating OpenGL context");
	SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
	if (!gl_context) {
		Terminal::out_error("Failed to initialize OpenGL context");
	}

	glewExperimental = GL_TRUE;
	Terminal::out_debug("Initilazing GL");
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Terminal::out_error("Failed to initialize GL context", false);
		std::cout << "GLEW error: " << error << std::endl;
		std::cout << "OpenGL error: " << glGetError() << std::endl;
		Terminal::freeze_exit();
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	color_program.compile_shaders("data/shaders/ColorShader.vert", "data/shaders/ColorShader.frag");
	color_program.add_attribute("vertex_position");
	color_program.link_shaders();

	glViewport(0, 0, screen_width, screen_height);
	sprite.update(-1.0f, -1.0f);
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

	color_program.use();
	sprite.draw();
	color_program.unuse();

	SDL_GL_SwapWindow(window.get());
}

Game::~Game() {
	Terminal::out_debug("Cleaning up game class for " + name);
}

} // Engine
