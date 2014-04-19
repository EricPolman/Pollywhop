#include "Renderer.h"
#include <glew/glew.h>
#include <gl/GL.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <time.h>

using namespace PW::Graphics;

static const GLchar* vertexSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
"in vec3 position;"
"void main() {"
"   gl_Position = projection * view * model * vec4(position, 1.0);"
"}";
static const GLchar* fragmentSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(triangleColor);"
"}";

static glm::mat4 view = glm::lookAt(
  glm::vec3(0, 1.2f, 2.0f),
  glm::vec3(0.0f, 0.0f, 0.0f),
  glm::vec3(0.0f, 0.0f, 1.0f)
);

void Renderer::Render()
{
  glBindVertexArray(_vao);
  glUseProgram(_shaderProgram);

  float time = glfwGetTime();
  glUniform4f(_uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 1.0f, 1.0f);
  glm::mat4 trans;
  trans = glm::rotate(
    trans,
    (float)clock() / (float)CLOCKS_PER_SEC * 180.0f,
    glm::vec3(0.0f, 1.0f, 0.0f)
    );
  glUniformMatrix4fv(_model, 1, GL_FALSE, glm::value_ptr(trans));

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

  _model = glGetUniformLocation(_shaderProgram, "model");
  _view = glGetUniformLocation(_shaderProgram, "view");
  glUniformMatrix4fv(_view, 1, GL_FALSE, glm::value_ptr(view));
  _projection = glGetUniformLocation(_shaderProgram, "projection");
  int width, height;
  glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
  glm::mat4 proj = glm::perspective(60.0f, (float)width / (float)height, 0.1f, 1000.0f);
  glUniformMatrix4fv(_projection, 1, GL_FALSE, glm::value_ptr(proj));

  _uniColor = glGetUniformLocation(_shaderProgram, "triangleColor");

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
}