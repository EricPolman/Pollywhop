#include "Mesh.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

using namespace PW::Graphics;

typedef glm::vec3 Vertex;
typedef glm::vec2 TexCoord;

const GLchar* vertexSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"in vec3 position;"
"void main() {"
"   gl_Position = vec4(position, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(triangleColor);"
"}";

Mesh::~Mesh()
{
}


class Mesh_Impl : public Mesh
{
public:
  virtual void Load()
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    _vertices.push_back(Vertex(0.0f, 0.5f, 0.0f));
    _vertices.push_back(Vertex(0.5f, -0.5f, 0.0f));
    _vertices.push_back(Vertex(-0.5f, -0.5f, 0.0f));
    glGenBuffers(1, &vbo); // Generate 1 buffer

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices.front(), GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    _uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform4f(_uniColor, 1.0f, 0.0f, 0.0f, 1.0f);
  }

  virtual void Render()
  {
    float time = glfwGetTime();
    glUniform4f(_uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f, 1.0f);

    // Bind
    glBindVertexArray(vao);
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  virtual void Unload()
  {

  }
protected:
  GLuint vao, vbo, shaderProgram;
  GLint _uniColor;
  std::vector<Vertex> _vertices;
  std::vector<Vertex> _normals;
  std::vector<TexCoord> _texCoords;
  std::vector<unsigned int> _vertexIndices;
  std::vector<unsigned int> _normalIndices;
  std::vector<unsigned int> _texCoordIndices;
};


std::shared_ptr<Mesh> Mesh::Create()
{
  return std::shared_ptr<Mesh>(new Mesh_Impl());
}