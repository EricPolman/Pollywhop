#include "Engine.h"
#include "Graphics/Window.h"

#include <iostream>
#include <glew\glew.h>
#include <GLFW\glfw3.h>

#include "Graphics/DemoTriangleMesh.h"
#include "Graphics/Renderer.h"

using namespace PW;

Engine::~Engine()
{
}

std::shared_ptr<Graphics::Mesh> mesh;
std::shared_ptr<Graphics::Renderer> renderer;

class Engine_Impl : public Engine
{
  virtual ~Engine_Impl()
  {
  }

  virtual void Initialize()
  {
    glfwInit();
  }
  virtual void OpenWindow(int a_width, int a_height, std::string a_name)
  {
    _window = Graphics::Window::Create(a_width, a_height, a_name, this);
    _window->Open();

    // TODO: Abstract away into separate rendering class?
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewInitResult;
    glewInitResult = glewInit();

    if (glewInitResult != GLEW_OK) {
      std::cerr << "ERROR: " << glewGetErrorString(glewInitResult) << std::endl;
      exit(EXIT_FAILURE);
    }

    //mesh = Graphics::DemoTriangleMesh::Create();
    //mesh->Load("");
    mesh.reset(new Graphics::Mesh);
    mesh->Load("Resources/Meshes/cube.obj");
    renderer.reset(new Graphics::Renderer());
    renderer->SetMesh(mesh);
  }

  virtual void Run()
  {
    _window->Update();
  }

  /*
   *  Called from Window, is just the Update
   */
  virtual void Update()
  {
    renderer->Render();
  }
  virtual void Render()
  {
  }

private:
  std::shared_ptr<Graphics::Window> _window;
};

std::unique_ptr<Engine> Engine::Create()
{
  return std::unique_ptr<Engine>(new Engine_Impl());
}