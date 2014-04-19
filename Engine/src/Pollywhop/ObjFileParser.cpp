#include "ObjFileParser.h"
#include "Graphics\Mesh.h"
#include <iostream>

using namespace PW;

void ObjFileParser::Parse(const std::string& a_path, Graphics::Mesh& a_mesh)
{
  //Used http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/ \
    for learning how to load an .OBJ model.
  FILE* file = fopen(a_path.c_str(), "r");
  if (!file)
  {
    std::cout << a_path.c_str() << std::endl;
    assert(0 && "Can't open file!");
  }

  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvcoords;

  std::vector<unsigned int> normalIndices;
  std::vector<unsigned int> vertexIndices;
  std::vector<unsigned int> uvcoordIndices;

  while (1)
  {
    char lineHeader[128];

    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break;

    if (strcmp(lineHeader, "v") == 0) //First character of line is "v", indicating vertex
    {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      vertices.push_back(vertex);
    }
    else if (strcmp(lineHeader, "vt") == 0)
    {
      glm::vec2 uvCoord;
      fscanf(file, "%f %f\n", &uvCoord.x, &uvCoord.y);
      uvcoords.push_back(uvCoord);
    }
    else if (strcmp(lineHeader, "vn") == 0)
    {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      normals.push_back(normal);
    }
    else if (strcmp(lineHeader, "f") == 0)
    {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
        &vertexIndex[0], &uvIndex[0], &normalIndex[0],
        &vertexIndex[1], &uvIndex[1], &normalIndex[1],
        &vertexIndex[2], &uvIndex[2], &normalIndex[2]
        );

      if (matches != 9){
        assert(0 && "Error found in your file.");
      }

      vertexIndices.push_back(vertexIndex[0] - 1);
      vertexIndices.push_back(vertexIndex[1] - 1);
      vertexIndices.push_back(vertexIndex[2] - 1);
      uvcoordIndices.push_back(uvIndex[0] - 1);
      uvcoordIndices.push_back(uvIndex[1] - 1);
      uvcoordIndices.push_back(uvIndex[2] - 1);
      normalIndices.push_back(normalIndex[0] - 1);
      normalIndices.push_back(normalIndex[1] - 1);
      normalIndices.push_back(normalIndex[2] - 1);
    }
  }
  fclose(file);

  a_mesh.SetVertices(vertices);
  a_mesh.SetNormals(normals);
  a_mesh.SetTexCoords(uvcoords);

  a_mesh.SetVertexIndices(vertexIndices);
  a_mesh.SetNormalIndices(normalIndices);
  a_mesh.SetTexCoordIndices(uvcoordIndices);
}