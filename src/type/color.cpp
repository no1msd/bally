#include "color.hpp"

color::color(): m_r(0), m_g(0), m_b(0) {
}

color::color(double p_r, double p_g, double p_b): m_r(p_r), m_g(p_g), m_b(p_b) {
}

color color::operator+(const color& c) const {
  return color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b);
}

color color::operator*(double f) const {
  return color(m_r * f, m_g * f, m_b * f);
}

color color::operator*(const color& c) const {
  return color(m_r * c.m_r, m_g * c.m_g, m_b * c.m_b);
}

color color::operator/(double f) const {
  return color(m_r / f, m_g / f, m_b / f);
}

double color::r() const {
  return m_r;
}

double color::g() const {
  return m_g;
}

double color::b() const {
  return m_b;
}
