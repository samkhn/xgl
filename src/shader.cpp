#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertex_path, const char *fragment_path) {
  std::string vertex_code;
  std::string fragment_code;
  std::ifstream vertex_shader_file;
  std::ifstream fragment_shader_file;
  vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragment_shader_file.exceptions(std::ifstream::failbit |
                                  std::ifstream::badbit);
  try {
    vertex_shader_file.open(vertex_path);
    fragment_shader_file.open(fragment_path);
    std::stringstream vertex_shader_stream, fragment_shader_stream;
    vertex_shader_stream << vertex_shader_file.rdbuf();
    fragment_shader_stream << fragment_shader_file.rdbuf();
    vertex_shader_file.close();
    fragment_shader_file.close();
    vertex_code = vertex_shader_stream.str();
    fragment_code = fragment_shader_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_READ_SUCCESSFULLY_READ\n";
  }
  const char *vertex_shader_code = vertex_code.c_str();
  const char *fragment_shader_code = fragment_code.c_str();

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_shader_code, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_shader_code, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  id = glCreateProgram();

  glAttachShader(id, vertexShader);
  glAttachShader(id, fragmentShader);
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() { glUseProgram(id); }

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
