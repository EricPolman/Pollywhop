#pragma once
#include <memory>
#include "Mesh.h"

namespace PW
{
  namespace Graphics
  {
    class Renderer
    {
    public:
      Renderer(){}
      ~Renderer(){}

      void Render();

      void SetMesh(std::shared_ptr<Mesh> a_mesh);//
      std::shared_ptr<Mesh> GetMesh() { return _mesh; }
    private:
      std::shared_ptr<Mesh> _mesh;
      unsigned int _vao, _shaderProgram, _uniColor, _model, _view, _projection;
    };
  }
}
