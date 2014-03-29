#include "Window.h"
#include <iostream>
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <time.h>

using namespace PW::Graphics;

const GLchar* vertexSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"in vec2 position;"
"void main() {"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"uniform vec4 triangleColor;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(triangleColor);"
"}";

Window::~Window()
{
}

class Window_Impl : public Window
{
public:
  Window_Impl(int a_width, int a_height, 
    std::string a_name, PW::Engine* a_engine)
    : _width(a_width), _height(a_height), _name(a_name), 
      _engine(a_engine), _handle(0)
  {

  }

  virtual void Open()
  {
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _glfwWindow =
      glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(_glfwWindow);
  }
  virtual void Close()
  {
    glfwTerminate();
  }
  virtual void Update()
  {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    float vertices[] = {
      0.0f, 0.5f, // Vertex 1 (X, Y)
      0.5f, -0.5f, // Vertex 2 (X, Y)
      -0.5f, -0.5f  // Vertex 3 (X, Y)
    };
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform4f(uniColor, 1.0f, 0.0f, 0.0f, 1.0f);

    glClearColor(0, 0, 0, 0);

    while (!glfwWindowShouldClose(_glfwWindow))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      float time = (float)clock() / (float)CLOCKS_PER_SEC;
      glUniform4f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f, 1.0f);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      _engine->Update();
      _engine->Render();

      glfwPollEvents();
      glfwSwapBuffers(_glfwWindow);
    }
  }

  virtual int GetWidth()
  {
    return _width;
  }
  virtual int GetHeight()
  {
    return _height;
  }

private:
  GLFWwindow* _glfwWindow;
  int _width, _height, _handle;
  std::string _name;
  PW::Engine* _engine;
};

std::shared_ptr<Window> Window::Create
(int a_width, int a_height, std::string a_name, PW::Engine* a_engine)
{
  return std::shared_ptr<Window>(
    new Window_Impl(a_width, a_height, a_name, a_engine)
    );
}
