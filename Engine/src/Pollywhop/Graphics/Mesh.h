#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glm\glm.hpp>

namespace PW
{
  namespace Graphics
  {
    class Mesh
    {
      friend class Renderer;
    public:
      virtual ~Mesh();

      virtual void Load(const std::string& a_path);
      virtual void Render();
      virtual void Unload();

      void SetVertices(const std::vector<glm::vec3>&);
      void SetNormals(const std::vector<glm::vec3>&);
      void SetTexCoords(const std::vector<glm::vec2>&);

      void SetVertexIndices(const std::vector<unsigned int>&);
      void SetNormalIndices(const std::vector<unsigned int>&);
      void SetTexCoordIndices(const std::vector<unsigned int>&);

      static std::shared_ptr<Mesh> Create();
    protected:
      std::vector<glm::vec3> _vertices, _normals;
      std::vector<glm::vec2> _texCoords;
      std::vector<unsigned int> _vertexIndices, _normalIndices, _texCoordIndices;
      unsigned int _vbo, _ebo; // Vertices
    private:
      void ResetBuffers();
    };
  }
}