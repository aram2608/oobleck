#include "../include/shader.h"

Shader CompileShader() {
  const GLchar* v_shader =
      "#version 330 core\n"
      "layout (location = 0) in vec4 vertex;\n"
      "out vec2 TexCoords;\n"
      "uniform mat4 projection;\n"
      "void main()\n"
      "{\n"
      "  gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
      "  TexCoords = vertex.zw;\n"
      "}\n";
  const GLchar* f_shader =
      "#version 330 core\n"
      "in vec2 TexCoords;\n"
      "out vec4 FragColor;\n"
      "uniform sampler2D text;\n"
      "uniform vec3 textColor;\n"
      "void main()\n"
      "{\n"
      "  float alpha = texture(text, TexCoords).r;\n"
      "  FragColor = vec4(textColor, alpha);\n"
      "}\n";
  unsigned int vertex;
  unsigned int fragment;
  // Vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &v_shader, NULL);
  glCompileShader(vertex);
  if (!CheckCompileError(vertex, "VERTEX")) {
    exit(1);
  }
  // Fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &f_shader, NULL);
  glCompileShader(fragment);
  if (!CheckCompileError(fragment, "FRAGMENT")) {
    exit(1);
  }
  unsigned int ID;
  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  if (!CheckCompileError(ID, "PROGRAM")) {
    exit(1);
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  Shader shader = {
      .ID = ID,
  };
  return shader;
}

bool CheckCompileError(GLuint shader, char* type) {
  GLint success;
  GLchar infoLog[1024];
  if (strcmp(type, "PROGRAM") == 0) {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      printf("Failed to compile shader: %s\n", infoLog);
      return false;
    }
  } else {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      printf("Failed to compile shader: %s\n", infoLog);
      return false;
    }
  }
  return true;
}