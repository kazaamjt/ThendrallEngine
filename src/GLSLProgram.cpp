#include "GLSLProgram.hpp"

#include <fstream>
#include <sstream>
#include <vector>

#include "Terminal.hpp"

GLSLProgram::GLSLProgram(/* args */):
	program_id(0),
	vertex_shader_id(0),
	fragment_shader_id(0)
{

}

void GLSLProgram::compile_shaders(const std::string &vertex_shader, const std::string &fragment_shader) {
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	if (vertex_shader_id == 0) {
		Terminal::out_error("Failed to create Vertex Shader.");
	}

	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (vertex_shader_id == 0) {
		Terminal::out_error("Failed to create fragment Shader.");
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
		Terminal::out_error("Shader failed to compile " + shader, false);
		std::printf("%s\n", &(error[0]));
		Terminal::freeze_exit();
	}
}

GLSLProgram::~GLSLProgram() {

}
