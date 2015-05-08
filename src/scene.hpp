#pragma once

#include <memory>
#include <vector>

#include "object/object.hpp"
#include "light.hpp"
#include "type/intersection.hpp"
#include "type/ray.hpp"

class scene {
 private:
  double m_eye_distance;
  int m_screen_width, m_screen_height;
  std::vector<std::shared_ptr<object>> m_objects;
  std::vector<light> m_lights;
  intersection first_intersect(const ray& ray);
  color direct_light_source(const intersection& in);
  color trace(const ray& ray, int d);

public:
  scene(int w, int h);
  void add_object(std::shared_ptr<object> obj);
  void add_light(const light& light);
  std::vector<unsigned char> render(int sample);
};
