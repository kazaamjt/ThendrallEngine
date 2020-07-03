#include "GLSLProgram.hpp"

#include <fstream>
#include <sstream>
#include <vector>

#include "Terminal.hpp"

GLSLProgram::GLSLProgram(/* args */):
	number_of_attributes(0),
	program_id(0),
	vertex_shader_id(0),
	fragment_shader_id(0)
{

}

void GLSLProgram::compile_shaders(const std::string &vertex_shader, const std::string &fragment_shader) {
	program_id = glCreateProgram();
	Terminal::out_debug("Compiling shader program " + std::to_string(program_id));
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	if (vertex_shader_id == 0) {
		Terminal::out_error("Failed to allocate a vertex Shader id.");
	}

	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (vertex_shader_id == 0) {
		Terminal::out_error("Failed to allocate a fragment Shader id.");
	}

	compile_shader(vertex_shader, vertex_shader_id);
	compile_shader(fragment_shader, fragment_shader_id);
}

void GLSLProgram::compile_shader(const std::string &shader, GLuint shader_id) {
	
	std::ifstream file(shader);
	if (file.fail()) {
		Terminal::out_error("Failed to open file: " + shader);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();
	file.close();

	const char* c_content_ptr = content.c_str();
	glShaderSource(shader_id, 1, &c_content_ptr, nullptr);
	glCompileShader(shader_id);

	GLint success = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint max_length = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

		std::vector<char> error(max_length);
		glGetShaderInfoLog(shader_id, max_length, &max_length, &error[0]);

		glDeleteShader(shader_id);
		Terminal::out_error("Failed to compile shader " + shader, false);
		std::printf("%s\n", &(error[0]));
		Terminal::freeze_exit();
	}
}

void GLSLProgram::link_shaders() {
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	glLinkProgram(program_id);

	GLint is_linked = 0;
	glGetProgramiv(program_id, GL_LINK_STATUS, &is_linked);

	if (is_linked == GL_FALSE) {
		GLint max_length = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);

		std::vector<char> error(max_length);
		glGetShaderInfoLog(program_id, max_length, &max_length, &error[0]);

		glDeleteProgram(program_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);

		Terminal::out_error("Failed to link GLSL program " + std::to_string(program_id), false);
		std::printf("%s\n", &(error[0]));
		Terminal::freeze_exit();
	}

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

void GLSLProgram::add_attribute(const std::string &attribute_name) {
	if (program_id == 0) {
		Terminal::out_warning("Added attribute to program with id 0. ");
	}
	glBindAttribLocation(program_id, number_of_attributes++, attribute_name.c_str());
}

void GLSLProgram::use() {
	glUseProgram(program_id);
	for (int i = 0; i < number_of_attributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < number_of_attributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLSLProgram::~GLSLProgram() {

}
