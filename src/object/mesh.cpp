#include "mesh.hpp"

const vector& mesh::position() const {
  return m_position;
}

void mesh::position(const vector& p_position) {
  m_position = p_position;
  for(auto& polygon: m_polygons)
    polygon = polygon + p_position;
}

void mesh::rotate(double angle, axis rotation_axis) {
  for(auto& polygon: m_polygons)
    polygon.rotate(angle, rotation_axis);
}

intersection mesh::intersect(const ray& ray) {
  intersection final;
  double max_dist = 1e10f;
  for(auto& polygon: m_polygons) {
    intersection current = polygon.intersect(ray);
    if (current.intersects()) {
      vector dist = current.point() - ray.origin();
      double dist_abs = dist.abs();
      if (dist_abs < max_dist) {
        max_dist = dist_abs;
        final = current;
        final.obj(shared_from_this());
      }
    }
  }
  return final;
}
