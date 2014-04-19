#pragma once
#include <string>

namespace PW
{
  namespace Graphics { class Mesh; };

  class ObjFileParser
  {
  public:
    static void Parse(const std::string& a_path, Graphics::Mesh& a_mesh);
  };
};
