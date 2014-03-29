#include "Engine.h"
#include "Window.h"
#include <iostream>
#include <freeglut/freeglut.h>

using namespace PW;

Engine::~Engine()
{
}

class Engine_Impl : public Engine
{
  virtual ~Engine_Impl()
  {

  }

  virtual void Initialize()
  {

  }
  virtual void OpenWindow(int a_width, int a_height, std::string a_name)
  {
    _window = Window::Create(a_width, a_height, a_name);
    _window->Open();
  }

  virtual void Update()
  {
    glutMainLoop();
  }
  virtual void Draw()
  {
    
  }

private:
  std::shared_ptr<Window> _window;
};

std::unique_ptr<Engine> Engine::Create()
{
  return std::unique_ptr<Engine>(new Engine_Impl());
}