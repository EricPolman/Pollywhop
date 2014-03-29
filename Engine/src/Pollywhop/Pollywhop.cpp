#include <string>
#include "Engine.h"

int width = 800;
int height = 600;
std::string windowTitle = "Pollywhop Engine";

int main()//int argc, char* argv[])
{
  auto engine = PW::Engine::Create();
  engine->Initialize();
  engine->OpenWindow(width, height, windowTitle);

  engine->Run();

  exit(EXIT_SUCCESS);
}