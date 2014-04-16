#include "Object.h"
#include <iostream>

using namespace GameLayer;

unsigned int Object::g_currentId = 0;

Object::Object(std::weak_ptr<Object> a_parent, std::string a_name)
: m_parent(a_parent), m_id(g_currentId++), m_transform(Transform::Create()), 
m_name(a_name), m_isRoot(false)
{
}
Object::Object(std::string a_name)
: m_id(g_currentId++), m_transform(Transform::Create()),
m_name(a_name), m_isRoot(true)
{
}

Object::~Object()
{
}


void Object::SetParent(std::weak_ptr<Object> a_newParent)
{
  auto me = std::shared_ptr<Object>(this);
  a_newParent.lock()->AddChild(me);
  if (m_parent.lock().get() != nullptr)
  {
    m_parent.lock()->RemoveChild(me);
    m_parent = a_newParent;
  }
}

void Object::RemoveChild(std::shared_ptr<Object> a_child)
{
  for (auto i = m_children.begin(); i != m_children.end();)
  {
    if (*i == a_child)
    {
      i = m_children.erase(i);

      if (m_children.capacity() > m_children.size() * 4)
        m_children.shrink_to_fit();
    }
    else
      i++;
  }
}
void Object::RemoveChild(unsigned int a_childIndex)
{
  if (a_childIndex < m_children.size())
  {
    int index = 0;
    for (auto i = m_children.begin(); i != m_children.end();)
    {
      if (index == a_childIndex)
      {
        m_children.erase(i);
        if (m_children.capacity() > m_children.size() * 4)
          m_children.shrink_to_fit();
        return;
      }

      index++;
    }
  }
}

void Object::AddChild(std::shared_ptr<Object> a_child)
{
  m_children.push_back(a_child);
}


void Object::Update(float a_deltaTime)
{
  Update(a_deltaTime);
  for (auto i = m_children.begin(); i != m_children.end(); i++)
  {
    i->get()->Update(a_deltaTime);
  }
}


void Object::Render()
{
  m_transform->Push();

  //if (m_renderer.get() != nullptr)
  //  m_renderer->Render();

  for (auto i = m_children.begin(); i != m_children.end(); i++)
  {
    i->get()->Render();
  }

  m_transform->Pop();
}

/*void Object::GetObjectsByName(std::string a_name,
  std::vector<std::weak_ptr<Object>>& a_objectVector)
{
  GameLayerCore->FindObjectsByName(a_name, a_objectVector);
}

std::weak_ptr<Object> Object::GetObjectById(unsigned int a_id)
{
  return GameLayerCore->FindObject(a_id);
}*/


std::weak_ptr<Object> Object::FindObject(unsigned int a_id)
{
  for (auto i = m_children.begin(); i != m_children.end(); i++)
  {
    if (i->get()->GetId() == a_id)
    {
      return std::weak_ptr<Object>(*i);
    }
    i->get()->FindObject(a_id);
  }
}

void Object::FindObjectsByName
(std::string a_name, std::vector<std::weak_ptr<Object>>& a_objectVec)
{
  for (auto i = m_children.begin(); i != m_children.end(); i++)
  {
    if (i->get()->GetName() == a_name)
    {
      a_objectVec.push_back(std::weak_ptr<Object>(*i));
    }
    i->get()->FindObjectsByName(a_name, a_objectVec);
  }
}
