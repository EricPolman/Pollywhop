#pragma once
#include "Mesh.h"

namespace PW
{
  namespace Graphics
  {
    class DemoTriangleMesh :
      public Mesh
    {
    public:
      virtual ~DemoTriangleMesh(){}

      virtual void Load(const std::string& a_path) = 0;
      virtual void Render() = 0;
      virtual void Unload() = 0;

      static std::shared_ptr<DemoTriangleMesh> Create();
    };
  }
}
