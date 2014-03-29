#pragma once
#include <memory>
#include <string>

namespace PW
{
  class Engine
  {
  public:
    virtual ~Engine();

    virtual void Initialize() = 0;
    virtual void OpenWindow(int a_width, int a_height, std::string a_name) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    static std::unique_ptr<Engine> Create();
  };
}
