#include "Mesh.h"
#include "../ObjFileParser.h"
#include <glew/glew.h>
#include <gl/GL.h>

using namespace PW::Graphics;

Mesh::~Mesh()
{
  ResetBuffers();
}

void Mesh::Load(const std::string& a_path)
{
  if (a_path.find(".obj"))
  {
    ObjFileParser::Parse(a_path, *this);
  }

  glGenBuffers(1, &_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    sizeof(unsigned int)* _vertexIndices.size(), &_vertexIndices.front(), GL_STATIC_DRAW);

  glGenBuffers(1, &_vbo); // Generate 1 buffer

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices.front(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Render()
{
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glDrawElements(GL_TRIANGLES, _vertexIndices.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Unload()
{
}

void Mesh::ResetBuffers()
{
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
}

void Mesh::SetVertices(const std::vector<glm::vec3>& a_data)
{
  _vertices.clear();
  for (auto iter : a_data) _vertices.push_back(iter);
}
void Mesh::SetNormals(const std::vector<glm::vec3>& a_data)
{
  _normals.clear();
  for (auto iter : a_data) _normals.push_back(iter);
}
void Mesh::SetTexCoords(const std::vector<glm::vec2>& a_data)
{
  _texCoords.clear();
  for (auto iter : a_data) _texCoords.push_back(iter);
}

void Mesh::SetVertexIndices(const std::vector<unsigned int>& a_data)
{
  _vertexIndices.clear();
  for (auto iter : a_data) _vertexIndices.push_back(iter);
}
void Mesh::SetNormalIndices(const std::vector<unsigned int>& a_data)
{
  _normalIndices.clear();
  for (auto iter : a_data) _normalIndices.push_back(iter);
}
void Mesh::SetTexCoordIndices(const std::vector<unsigned int>& a_data)
{
  _texCoordIndices.clear();
  for (auto iter : a_data) _texCoordIndices.push_back(iter);
}


/*std::shared_ptr<Mesh> Mesh::Create()
{
  return std::shared_ptr<Mesh>(new Mesh_Impl());
}*/