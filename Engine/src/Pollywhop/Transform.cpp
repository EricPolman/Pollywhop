#include "Transform.h"
#include <glm\gtc\quaternion.hpp>

using namespace GameLayer;

class Transform_OpenGL : public Transform
{
public:
  Transform_OpenGL() :
    m_position(), m_rotation(), m_scale(1)
  {
  }


  ~Transform_OpenGL()
  {
  }

  virtual void SetPosition(const glm::vec3& a_position)
  {
    m_position = a_position;
  }
  virtual void SetRotation(float a_rotation)
  {
    // TODO
    //m_rotation = a_rotation;
  }
  virtual void SetScale(float a_scale)
  {
    m_scale = a_scale;
  }

  virtual const glm::vec3& GetPosition() const
  {
    return m_position;
  }
  virtual const glm::vec3& GetRotationAsEuler() const
  {
    return glm::vec3(0, 0, 0);
    //return m_rotation;
  }
  virtual const float GetScale() const
  {
    return m_scale;
  }

  virtual void Translate(const glm::vec3& a_amount)
  {
    m_position += a_amount;
  }
  virtual void Rotate(float a_amount)
  {
    // TODO
    //m_rotation += a_amount;
  }
  virtual void Scale(float a_amount)
  {
    m_scale *= a_amount;
  }

  virtual void Push()
  {
    // TODO: Figure out what to do here.
    // Posibility: Use a static variable to keep track of current transformation.
  }
  virtual void Pop()
  {
    // TODO: Figure out what to do here.
  }
private:
  glm::vec3 m_position;
  glm::quat m_rotation;
  float m_scale;
};


std::shared_ptr<Transform> Transform::Create()
{
  return std::shared_ptr<Transform>(new Transform_OpenGL());
}