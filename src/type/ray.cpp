#include "ray.hpp"

ray::ray(const vector& p_origin, const vector& p_direction):
    m_origin(p_origin), m_direction(p_direction)
{
}

const vector& ray::origin() const {
  return m_origin;
}

const vector& ray::direction() const {
  return m_direction;
}
