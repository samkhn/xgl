#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <glad/glad.h>

#include <string>

class Shader {
 public:
  unsigned int id;
  Shader(const char *vertex_path, const char *fragment_path);
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};

#endif
