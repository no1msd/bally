#include "plane.hpp"

plane::plane(
    const material& p_material,
    const vector& p_position,
    double p_size,
    axis vector_axis,
    bool flip):
    m_material(p_material),
    m_size(p_size)
{
  double half = m_size / 2;
  if (!flip) {
    m_polygons.push_back(
        {cv(-half,  half, vector_axis),
         cv( half,  half, vector_axis),
         cv(-half, -half, vector_axis)});
    m_polygons.push_back(
        {cv( half,  half, vector_axis),
         cv( half, -half, vector_axis),
         cv(-half, -half, vector_axis)});
  } else {
    m_polygons.push_back(
        {cv(-half,  half, vector_axis),
         cv(-half, -half, vector_axis),
         cv( half,  half, vector_axis)});
    m_polygons.push_back(
        {cv( half,  half, vector_axis),
         cv(-half, -half, vector_axis),
         cv( half, -half, vector_axis)});
  }

  for(auto& polygon: m_polygons)
    polygon = polygon + p_position;
}

color plane::object_color(const vector& point) {
  return m_material.diffuse();
}

vector plane::cv(double x, double y, axis vector_axis) {
  switch (vector_axis) {
    case axis::x:
      return {0, x, y};
    case axis::y:
      return {x, 0, y};
    case axis::z:
      return {x, y, 0};
  };
  return {0, 0, 0};
}

material plane::object_material() {
  return m_material;
}
