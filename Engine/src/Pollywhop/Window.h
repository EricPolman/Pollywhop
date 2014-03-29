#pragma once
#include <memory>
#include <string>

namespace PW
{
  class Window
  {
  public:
    virtual ~Window();

    virtual void Open() = 0;
    virtual void Close() = 0;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;

    static std::shared_ptr<Window>
      Create(int a_width, int a_height, std::string a_name);
  };
}