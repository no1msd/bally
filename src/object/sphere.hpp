#pragma once

#include <memory>

#include "object/object.hpp"
#include "type/intersection.hpp"
#include "type/ray.hpp"
#include "type/material.hpp"
#include "type/color.hpp"
#include "texture/texture.hpp"

class sphere: public object, public std::enable_shared_from_this<sphere> {
private:
  std::shared_ptr<texture> m_texture;
  material m_material;
  vector m_origin;
  double m_radius;
  double m_y_rotation;

public:
  sphere(
      const material& p_material,
      std::shared_ptr<texture> p_texture,
      const vector& p_origin,
      double p_radius,
      double p_y_rotation);
  intersection intersect(const ray& ray) override;
  color object_color(const vector& position) override;
  material object_material() override;
  const vector& origin() const;
  double radius() const;
};
