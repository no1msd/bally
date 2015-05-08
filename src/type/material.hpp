#pragma once

#include "type/color.hpp"

class material {
 public:
  material();
  material(
      const color& p_color,
      double p_reflect,
      double p_shininess,
      double p_scatter);

  color diffuse() const;
  double reflect() const;
  double shininess() const;
  double scatter() const;

 private:
  color m_color;
  double m_reflect;
  double m_shininess;
  double m_scatter;
};
