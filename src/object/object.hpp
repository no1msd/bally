#pragma once

#include "type/material.hpp"
#include "type/intersection.hpp"
#include "type/vector.hpp"
#include "type/color.hpp"
#include "type/ray.hpp"

class object {
 public:
  virtual ~object() {}
  virtual intersection intersect(const ray& ray) = 0;
  virtual color object_color(const vector& point) = 0;
  virtual material object_material() = 0;
};