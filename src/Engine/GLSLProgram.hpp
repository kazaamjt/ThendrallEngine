#pragma once
#include <string>

#include <GL/glew.h>

namespace Engine {

class GLSLProgram {
public:
	GLSLProgram(const std::string &name);
	~GLSLProgram();

	void compile_shaders(const std::string &vertex_shader, const std::string &fragment_shader);
	void link_shaders();

	void add_attribute(const std::string &attribute_name);

	GLint get_uniform_location(const std::string &unifrom_name);

	void use();
	void unuse();

private:
	std::string name;

	int number_of_attributes;
	GLuint program_id;
	GLuint vertex_shader_id;
	GLuint fragment_shader_id;

	void compile_shader(const std::string &shader, GLuint shader_id);
};
} // Engine
