#include "light.hpp"

#include <cmath>
#include <random>

#include "utils.hpp"

light::light(): m_intensity(1), m_specular(1), m_radius(0), m_angle(0) {
}

light::light(
    const vector& p_position,
    const vector& p_direction,
    const color& p_color,
    double p_intensity,
    double p_specular,
    double p_radius,
    double p_angle):
    m_position(p_position),
    m_direction(p_direction),
    m_color(p_color),
    m_intensity(p_intensity),
    m_specular(p_specular),
    m_radius(p_radius),
    m_angle(p_angle)
{
  m_direction.normalize();
}

ray light::shadow_ray(const vector& position) {
  vector light_dir = m_position - position;
  double light_dist = light_dir.abs();
  light_dir.normalize();
  double alpha = std::atan2(m_radius, light_dist);
  alpha = (alpha / constants::pi) * 180;

  double b = get_rand() * 2.0 * constants::pi;
  double t = get_rand();
  double rotU = sin(b) * t;
  double rotV = cos(b) * t;

  light_dir.rotate(alpha * rotU, axis::z);
  light_dir.rotate(alpha * rotV, axis::x);
  ray shadow_ray(position, light_dir);

  return shadow_ray;
}

bool light::effective(const vector& v) {
  if (m_angle == 0)
    return true;
  ray ray = shadow_ray(v);
  vector r = ray.direction() * -1;
  r.normalize();
  m_direction.normalize();
  return std::acos(r * m_direction) <= (m_angle/ 180.0) * constants::pi;
}

const vector& light::position() const {
  return m_position;
}

const vector& light::direction() const {
  return m_direction;
}

const color& light::light_color() const {
  return m_color;
}

double light::intensity() const {
  return m_intensity;
}

double light::specular() const {
  return m_specular;
}

double light::radius() const {
  return m_radius;
}

double light::angle() const {
  return m_angle;
}
