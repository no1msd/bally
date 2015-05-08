#include "polygon.hpp"

polygon::polygon():
    m_p1(0, 0, 0), m_p2(1, 0, 0), m_p3(0, 1, 0), m_normal(0, 0, 1)
{
}

polygon::polygon(const vector& p_p1, const vector& p_p2, const vector& p_p3):
    m_p1(p_p1), m_p2(p_p2), m_p3(p_p3)
{
  m_normal = (m_p2 - m_p1) % (m_p3 - m_p1);
  m_normal.normalize();
}

intersection polygon::intersect(const ray& ray) {
  double min = constants::epsilon;
  double distance = (((ray.origin() - m_p1) * m_normal) /
      (ray.direction() * m_normal)) * -1;

  if (distance < min)
    return intersection();

  vector p = ray.origin() + ray.direction() * distance;

  if ((((m_p2 - m_p1) % (p - m_p1)) * m_normal < min) ||
      (((m_p3 - m_p2) % (p - m_p2)) * m_normal < min) ||
      (((m_p1 - m_p3) % (p - m_p3)) * m_normal < min))
    return intersection();

  return intersection(p, m_normal, nullptr);
}

polygon polygon::operator+(const vector& v) {
  return polygon(m_p1 + v, m_p2 + v, m_p3 + v);
}

void polygon::rotate(double angle, axis rotation_axis) {
  m_p1.rotate(angle, rotation_axis);
  m_p2.rotate(angle, rotation_axis);
  m_p3.rotate(angle, rotation_axis);
}
