#include "DemoTriangleMesh.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

using namespace PW::Graphics;

typedef glm::vec3 Vertex;
typedef glm::vec2 TexCoord;

const GLuint elements[] = {
  0, 1, 2
};

class DemoTriangleMesh_Impl : public DemoTriangleMesh
{
public:
  virtual void Load(const std::string& a_path)
  {
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
      sizeof(elements), elements, GL_STATIC_DRAW);

    _vertices.push_back(Vertex(0.0f, 0.5f, 0.0f));
    _vertices.push_back(Vertex(0.5f, -0.5f, 0.0f));
    _vertices.push_back(Vertex(-0.5f, -0.5f, 0.0f));
    glGenBuffers(1, &_vbo); // Generate 1 buffer

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices.front(), GL_STATIC_DRAW);

  }

  virtual void Render()
  {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  virtual void Unload()
  {

  }
protected:
  std::vector<Vertex> _vertices;
  std::vector<Vertex> _normals;
  std::vector<TexCoord> _texCoords;
  std::vector<unsigned int> _vertexIndices;
  std::vector<unsigned int> _normalIndices;
  std::vector<unsigned int> _texCoordIndices;
};


std::shared_ptr<DemoTriangleMesh> DemoTriangleMesh::Create()
{
  return std::shared_ptr<DemoTriangleMesh>(
    new DemoTriangleMesh_Impl()
  );
}