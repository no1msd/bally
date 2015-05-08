#include "vector.hpp"

#include <cmath>

#include "constants.hpp"

vector::vector(): m_x(0), m_y(0), m_z(0) {
}

vector::vector(double p_x, double p_y, double p_z):
    m_x(p_x), m_y(p_y), m_z(p_z)
{
}

vector& vector::operator=(const vector& v) {
  m_x = v.m_x;
  m_y = v.m_y;
  m_z = v.m_z;
  return *this;
}

vector vector::operator+(const vector& v) const {
  return vector(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
}

vector vector::operator-(const vector& v) const {
  return vector(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
}

vector vector::operator%(const vector& v) const {
  return vector(
      m_y * v.m_z - m_z * v.m_y,
      m_z * v.m_x - m_x * v.m_z,
      m_x * v.m_y - m_y * v.m_x);
}

vector vector::operator*(double f) const {
  return vector(m_x * f, m_y * f, m_z * f);
}

vector vector::operator/(double f) const {
  return vector(m_x / f, m_y / f, m_z / f);
}

double vector::operator*(const vector& v) const {
  return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

void vector::normalize() {
  double length = abs();
  m_x /= length;
  m_y /= length;
  m_z /= length;
}

double vector::abs() const {
  return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

void vector::rotate(double angle, axis rotation_axis) {
  angle = (angle / 180.0) * constants::pi;
  auto do_rotate = [angle](double& x, double& y) {
    double x0 = x;
    double y0 = y;
    x = x0 * std::cos(angle) - y0 * std::sin(angle);
    y = x0 * std::sin(angle) + y0 * std::cos(angle);
  };
  switch (rotation_axis) {
    case axis::x:
      do_rotate(m_z, m_y);
      break;
    case axis::y:
      do_rotate(m_x, m_z);
      break;
    case axis::z:
      do_rotate(m_x, m_y);
      break;
  }
}

double vector::x() const {
  return m_x;
}

double vector::y() const {
  return m_y;
}

double vector::z() const {
  return m_z;
}
