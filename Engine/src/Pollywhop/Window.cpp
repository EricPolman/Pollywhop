#include "Window.h"
#include <iostream>
#include <freeglut/freeglut.h>
#include <gl/GL.h>

using namespace PW;

void Resize(int, int);
void Render(void);

Window::~Window()
{
}

class Window_Impl : public Window
{
public:
  Window_Impl(int a_width, int a_height, std::string a_name)
    : _handle(0), _name(a_name)
  {
    g_width = a_width;
    g_height = a_height;
  }

  virtual void Open()
  {
    char *argv[1];
    int argc = 1;
    argv[0] = strdup("Pollywhop Engine");
    glutInit(&argc, argv);

    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
      GLUT_ACTION_ON_WINDOW_CLOSE,
      GLUT_ACTION_GLUTMAINLOOP_RETURNS
      );

    glutInitWindowSize(g_width, g_height);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    _handle = glutCreateWindow(_name.c_str());

    if (_handle < 1) {
      std::cerr << "ERROR: Could not create a new rendering window.\n";
      exit(EXIT_FAILURE);
    }

    glutReshapeFunc(Resize);
    glutDisplayFunc(Render);
  }
  virtual void Close()
  {

  }

  virtual int GetWidth()
  {
    return g_width;
  }
  virtual int GetHeight()
  {
    return g_height;
  }

  // Variables
  static int g_width, g_height;
  std::string _name;
  int _handle;
};
int Window_Impl::g_width = 0;
int Window_Impl::g_height = 0;

void Resize(int a_width, int a_height)
{
  Window_Impl::g_width = a_width;
  Window_Impl::g_height = a_height;
  glViewport(0, 0, a_width, a_height);
}
void Render(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glutSwapBuffers();
  glutPostRedisplay();
}

std::shared_ptr<Window> Window::Create
  (int a_width, int a_height, std::string a_name)
{
  return std::shared_ptr<Window>(new Window_Impl(a_width, a_height, a_name));
}
