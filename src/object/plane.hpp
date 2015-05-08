#pragma once

#include "object/mesh.hpp"

class plane: public mesh {
 public:
  plane(
      const material& p_material,
      const vector& p_position,
      double p_size,
      axis vector_axis,
      bool flip);
  color object_color(const vector& point) override;
  material object_material() override;

 private:
  material m_material;
  double m_size;
  vector cv(double x, double y, axis vector_axis);
};
