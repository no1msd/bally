#include "material.hpp"

material::material():
    m_color(1, 1, 1), m_reflect(0), m_shininess(0), m_scatter(0)
{
}

material::material(
    const color& p_color,
    double p_reflect,
    double p_shininess,
    double p_scatter):
    m_color(p_color),
    m_reflect(p_reflect),
    m_shininess(p_shininess),
    m_scatter(p_scatter)
{
}

color material::diffuse() const {
  return m_color;
}

double material::reflect() const {
  return m_reflect;
}

double material::shininess() const {
  return m_shininess;
}

double material::scatter() const {
  return m_scatter;
}
