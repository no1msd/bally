#pragma once

#include "constants.hpp"
#include "type/axis.hpp"
#include "type/color.hpp"
#include "type/vector.hpp"
#include "type/ray.hpp"

class light {
 public:
  light();
  light(
      const vector& p_position,
      const vector& p_direction,
      const color& p_color,
      double p_intensity,
      double p_specular,
      double p_radius,
      double p_angle);
  ray shadow_ray(const vector& p2);
  bool effective(const vector& v);

  const vector& position() const;
  const vector& direction() const;
  const color& light_color() const;
  double intensity() const;
  double specular() const;
  double radius() const;
  double angle() const;

 private:
  vector m_position;
  vector m_direction;
  color m_color;
  double m_intensity;
  double m_specular;
  double m_radius;
  double m_angle;
};
