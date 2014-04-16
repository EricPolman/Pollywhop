#pragma once
#include <glm\glm.hpp>
#include <memory>

namespace GameLayer
{
  class Transform
  {
  public:
    virtual ~Transform(){}

    virtual void SetPosition(const glm::vec3& a_position) = 0;
    virtual void SetRotation(float a_rotation) = 0;
    virtual void SetScale(float a_scale) = 0;

    virtual const glm::vec3& GetPosition() const = 0;
    virtual const glm::vec3& GetRotationAsEuler() const = 0;
    virtual const float GetScale() const = 0;

    virtual void Translate(const glm::vec3& a_amount) = 0;
    virtual void Rotate(float a_amount) = 0;
    virtual void Scale(float a_amount) = 0;

    virtual void Push() = 0;
    virtual void Pop() = 0;

    static std::shared_ptr<Transform> Create();
  };
};
