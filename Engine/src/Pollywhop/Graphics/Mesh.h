#pragma once
#include <memory>

namespace PW
{
  namespace Graphics
  {
    class Mesh
    {
    public:
      virtual ~Mesh();

      virtual void Load() = 0;
      virtual void Render() = 0;
      virtual void Unload() = 0;

      static std::shared_ptr<Mesh> Create();
    };
  }
}