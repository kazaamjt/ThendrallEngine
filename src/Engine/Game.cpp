#include "Game.hpp"

#include <GL/glew.h>

#include "Terminal.hpp"
#include "TextureLoader.hpp"

namespace Engine {

Game::Game(const std::string &_name):
	name(_name),
	window(nullptr),
	screen_width(1280),
	screen_height(720),
	state(GameState::INIT),
	sprite(-1.0f, -1.0f, 2.0f, 2.0f),
	color_shader("color_shader"),
	time(0)
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
		SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, sdl_window_flags),
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

	Terminal::out_debug("Loading shaders");
	color_shader.compile_shaders("data/shaders/ColorShader.vert", "data/shaders/ColorShader.frag");
	color_shader.add_attribute("vertex_position");
	color_shader.add_attribute("vertex_color");
	color_shader.add_attribute("vertex_uv");
	color_shader.link_shaders();

	glViewport(0, 0, screen_width, screen_height);
	sprite.update(-1.0f, -1.0f);
}

void Game::run() {
	init();
	texture = TextureLoader::load_png("dude");
	main_loop();
}

void Game::main_loop() {
	state = GameState::RUN;
	while (state != GameState::STOP) {
		process_input();
		time += 0.01f;
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

	color_shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	GLint sampler_uniform = color_shader.get_uniform_location("in_texture");
	glUniform1i(sampler_uniform, 0);

	GLint time_uniform = color_shader.get_uniform_location("time");
	glUniform1f(time_uniform, time);

	sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	color_shader.unuse();

	SDL_GL_SwapWindow(window.get());
}

Game::~Game() {
	Terminal::out_debug("Destructor called on Game object for " + name + ".");
	Terminal::out_debug("Destroying SDL window.");
	if (window) {
		SDL_DestroyWindow(window.get());
	}
	SDL_Quit();
}

} // Engine
