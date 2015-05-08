#include "intersection.hpp"

#include "object/object.hpp"

intersection::intersection(): m_intersects(false), m_obj(nullptr) {
}

intersection::intersection(
    const vector& p_point,
    const vector& p_normal,
    std::shared_ptr<object> p_obj):
    m_intersects(true),
    m_point(p_point),
    m_normal(p_normal),
    m_obj(p_obj)
{
}

bool intersection::intersects() const {
  return m_intersects;
}

std::shared_ptr<object> intersection::obj() const {
  return m_obj;
}

void intersection::obj(std::shared_ptr<object> p_object) {
  m_obj = p_object;
}

const vector& intersection::point() const {
  return m_point;
}

const vector& intersection::normal() const {
  return m_normal;
}
