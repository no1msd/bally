#include "sphere.hpp"

#include <cmath>

#include "constants.hpp"

sphere::sphere(
    const material& p_material,
    std::shared_ptr<texture> p_texture,
    const vector& p_origin,
    double p_radius,
    double p_y_rotation):
    m_texture(p_texture),
    m_material(p_material),
    m_origin(p_origin),
    m_radius(p_radius),
    m_y_rotation(p_y_rotation)
{
}

intersection sphere::intersect(const ray& ray) {
  vector L = m_origin - ray.origin();
  double tca = L * ray.direction();
  if (tca < 0)
    return intersection();

  double d2 = L * L - tca * tca;
  if (d2 > m_radius * m_radius)
    return intersection();

  double thc = std::sqrt(m_radius * m_radius - d2);
  double t = tca - thc;
  vector P = ray.origin() + ray.direction() * t;
  vector norm = P - m_origin;
  norm.normalize();

  return intersection(P, norm, shared_from_this());
}

color sphere::object_color(const vector& position) {
  if (m_texture == nullptr)
    return m_material.diffuse();

  vector r = position - m_origin;
  r.normalize();
  r.rotate(m_y_rotation, axis::y);

  double alpha = std::atan2(r.x(), r.z());
  double beta = std::atan2(std::sqrt(r.z() * r.z() + r.x() * r.x()), r.y());

  double u = (alpha + constants::pi) / (2 * constants::pi);
  double v = beta / constants::pi;

  return m_texture->pixel(u, v);
}

const vector& sphere::origin() const {
  return m_origin;
}

double sphere::radius() const {
  return m_radius;
}

material sphere::object_material() {
  return m_material;
}
