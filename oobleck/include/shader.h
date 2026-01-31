#ifndef SHADER_H_
#define SHADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct {
  unsigned int ID;
} Shader;

Shader CompileShader();

bool CheckCompileError(GLuint shader, char* type);

#endif