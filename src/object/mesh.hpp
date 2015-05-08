#pragma once

#include <vector>

#include "object/object.hpp"
#include "object/polygon.hpp"
#include "type/intersection.hpp"
#include "type/ray.hpp"

class mesh: public object, public std::enable_shared_from_this<mesh> {
 public:
  const vector& position() const;
  void position(const vector& p_position);
  void rotate(double angle, axis rotation_axis);
  intersection intersect(const ray& ray) override;

 protected:
  vector m_position;
  std::vector<polygon> m_polygons;
};
