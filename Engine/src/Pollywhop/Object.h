#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Transform.h"

namespace GameLayer
{
  class Object
  {
  public:
    Object(std::weak_ptr<Object> a_parent, std::string a_name);
    Object(std::string a_name);
    virtual ~Object();

    const std::string GetName() const { return m_name; }
    void SetName(std::string a_value) { m_name = a_value; }

    const unsigned int GetId() const { return m_id; }

    virtual void Update(float a_deltaTime);
    void Render();

    void SetParent(std::weak_ptr<Object> a_newParent);
    void RemoveChild(std::shared_ptr<Object> a_child);
    void RemoveChild(unsigned int a_childIndex);
    void AddChild(std::shared_ptr<Object> a_child);
    std::weak_ptr<Object> GetChild(int index) const
      { return std::weak_ptr<Object>(m_children[index]); }

    static void GetObjectsByName(std::string a_name,
      std::vector<std::weak_ptr<Object>>& a_objectVector);
    static std::weak_ptr<Object> GetObjectById(unsigned int a_id);

    std::shared_ptr<Transform> GetTransform() const { return m_transform; }
    //std::shared_ptr<Renderer> GetRenderer() const { return m_renderer; }

  protected:
    //std::shared_ptr<Renderer> m_renderer;
    std::vector<std::shared_ptr<Object>> m_children;
    std::weak_ptr<Object> m_parent;
    std::shared_ptr<Transform> m_transform;
    std::string m_name;
    bool m_isRoot;
  private:
    static unsigned int g_currentId;
    unsigned int m_id;

    std::weak_ptr<Object> FindObject(unsigned int a_id);
    void FindObjectsByName
      (std::string a_name, std::vector<std::weak_ptr<Object>>& a_objectVec);
  };
};
