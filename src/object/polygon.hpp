#pragma once

#include "constants.hpp"
#include "type/vector.hpp"
#include "type/intersection.hpp"
#include "type/ray.hpp"

class polygon {
 public:
  polygon();
  polygon(const vector& p_p1, const vector& p_p2, const vector& p_p3);
  intersection intersect(const ray& ray);
  polygon operator+(const vector& v);
  void rotate(double angle, axis rotation_axis);

 private:
  vector m_p1;
  vector m_p2;
  vector m_p3;
  vector m_normal;
};
