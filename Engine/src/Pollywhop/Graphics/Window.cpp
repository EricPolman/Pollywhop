#include "Window.h"
#include <iostream>
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

using namespace PW::Graphics;

void Resize(int, int);
void Render(void);

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
    while (!glfwWindowShouldClose(_glfwWindow))
    {
      glfwSwapBuffers(_glfwWindow);
      glfwPollEvents();

      _engine->Update();
      _engine->Render();
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
