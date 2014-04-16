#include "Window.h"
#include <iostream>
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <time.h>

using namespace PW::Graphics;

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
    glClearColor(0, 0, 0, 0);

    while (!glfwWindowShouldClose(_glfwWindow))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      _engine->Update();
      _engine->Render();

      glfwPollEvents();
      if (glfwGetKey(_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_glfwWindow, GL_TRUE);
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
