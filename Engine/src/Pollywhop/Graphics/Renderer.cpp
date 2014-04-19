#include "Renderer.h"
#include <glew/glew.h>
#include <gl/GL.h>
#include <GLFW\glfw3.h>

using namespace PW::Graphics;

static const GLchar* vertexSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"in vec3 position;"
"void main() {"
"   gl_Position = vec4(position, 1.0);"
"}";
static const GLchar* fragmentSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(triangleColor);"
"}";

void Renderer::Render()
{
  float time = glfwGetTime();
  glUniform4f(_uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f, 1.0f);

  glBindVertexArray(_vao);
  glUseProgram(_shaderProgram);
  _mesh->Render();
  glBindVertexArray(0);
  glUseProgram(0);
}

void Renderer::SetMesh(std::shared_ptr<Mesh> a_mesh)
{
  _mesh = a_mesh;
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, _mesh->_vbo);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  _shaderProgram = glCreateProgram();
  glAttachShader(_shaderProgram, vertexShader);
  glAttachShader(_shaderProgram, fragmentShader);

  glBindFragDataLocation(_shaderProgram, 0, "outColor");

  glLinkProgram(_shaderProgram);
  glUseProgram(_shaderProgram);

  GLint posAttrib = glGetAttribLocation(_shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

  _uniColor = glGetUniformLocation(_shaderProgram, "triangleColor");
  glUniform4f(_uniColor, 1.0f, 0.0f, 0.0f, 1.0f);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
}