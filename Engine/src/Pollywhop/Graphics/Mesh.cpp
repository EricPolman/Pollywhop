#include "Mesh.h"

using namespace PW::Graphics;

Mesh::~Mesh()
{
}


class Mesh_Impl : public Mesh
{
public:
  virtual void Load()
  {
  }

  virtual void Render()
  {
  }

  virtual void Unload()
  {

  }
protected:
};


/*std::shared_ptr<Mesh> Mesh::Create()
{
  return std::shared_ptr<Mesh>(new Mesh_Impl());
}*/