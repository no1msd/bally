#include "scene.hpp"

#include <cmath>
#include <iostream>

#include "utils.hpp"

intersection scene::first_intersect(const ray& ray) {
  intersection final;
  double max_dist = 1e10f;
  for(auto object: m_objects) {
    intersection current = object->intersect(ray);
    if (current.intersects()) {
      vector dist = current.point() - ray.origin();
      double dist_length = dist.abs();
      if (dist_length < max_dist) {
        max_dist = dist_length;
        final = current;
      }
    }
  }
  return final;
}

color scene::direct_light_source(const intersection& in) {
  color c;
  c = in.obj()->object_color(in.point()) * 0.2;

  for (auto& light: m_lights) {
    if (!light.effective(in.point()))
      continue;

    vector l = light.position() - in.point();
    double ldist = l.abs();
    l.normalize();
    ray shadow_ray = light.shadow_ray(in.point());
    intersection block = first_intersect(shadow_ray);

    double indist = (block.point() - in.point()).abs();
    if (!(block.intersects() && (indist < ldist))) {
      double ln = l * in.normal();
      c = c + (light.light_color() * in.obj()->object_color(in.point()) * ln *
          light.intensity());

      // specular
      if (in.obj()->object_material().shininess() != 0) {
        double c1 = (in.normal() * l) * -1;
        vector r = l + (in.normal() * 2 * c1);
        r.normalize();
        vector v = in.point() * -1;
        v.normalize();

        c = c + light.light_color() * light.specular() *
            std::pow(r * v, in.obj()->object_material().shininess());
      }
    }
  }
  return c;
}

color scene::trace(const ray& in_ray, int d) {
  color c;
  if (d > 0)
    return c;
  intersection in = first_intersect(in_ray);

  if (!in.intersects())
    return c;

  material mat = in.obj()->object_material();

  // diffuse
  c = c + direct_light_source(in);

  // reflection
  if (mat.reflect() > 0) {
    double c1 = (in.normal() * in_ray.direction()) * -1;
    vector ref = in_ray.direction() + (in.normal() * 2 * c1);
    double ref_dist = ref.abs();
    ref.normalize();

    double alpha = std::atan2(mat.scatter(), ref_dist);
    alpha = (alpha / constants::pi) * 180;
    double b = get_rand() * 2.0 * constants::pi;
    double t = get_rand();
    double rotU = sin(b) * t;
    double rotV = cos(b) * t;
    ref.rotate(alpha * rotU, axis::z);
    ref.rotate(alpha * rotV, axis::x);

    ray ref_ray{in.point(), ref};
    c = c + (trace(ref_ray, d + 1) * mat.reflect());
  };

  return c;
}

scene::scene(int w, int h):
    m_eye_distance(50), m_screen_width(w), m_screen_height(h)
{
}

void scene::add_object(std::shared_ptr<object> obj) {
  m_objects.push_back(obj);
}

void scene::add_light(const light& light) {
  m_lights.push_back(light);
}

std::vector<unsigned char> scene::render(int sample) {
  std::vector<unsigned char> data;
  double pixel_size = 100.0 / (double)m_screen_width;

  vector eye(0, 0, -1 * m_eye_distance);
  for (int y = m_screen_height - 1; y >= 0; y--) {
    //std::cout.precision(2);
    //std::cout << ((y * m_screen_width) /
    //    (double)(m_screen_width * m_screen_height)) * 100.0 << "%" << std::endl;
    double sy = y * pixel_size - 50.0;
    for (int x = 0; x < m_screen_width; x++) {
      double sx = x * pixel_size - 50.0;
      color c;

      for (double a = 0; a < sample; a++) {
        for (double b = 0; b < sample; b++) {
          double sample_size = pixel_size / sample;
          double rand_x = get_rand();
          double rand_y = get_rand();
          vector samp_pos(
              sx + a * sample_size + rand_x * sample_size,
              sy + b * sample_size + rand_y * sample_size,
              0);

          // the original ray..
          vector ray_direction = samp_pos - eye;
          ray r(eye, ray_direction);

          // the focal plane..
          vector focal_normal(0, 0, -1);
          double focal_distance = 140;

          // the intersection of the original ray and the focal plane
          double t = ((focal_normal * eye + focal_distance) * -1) /
                     (focal_normal * ray_direction);
          vector focal_int = eye + ray_direction * t;

          // the random start point on the lens
          vector eye2 = eye + vector(get_rand() * 7.0, get_rand() * 7.0, 0);

          // the new ray
          vector ray_direction2 = focal_int - eye2;
          ray_direction2.normalize();
          ray_direction2.rotate(-5, axis::x);
          eye2 = eye2 + vector(0, -100, 50);
          ray r2(eye2, ray_direction2);

          color samp_col = trace(r2, 0);
          c = c + samp_col;
        }
      }
      c = c / (sample * sample);

      auto add_pixel_data = [&data](double val) {
        if(val < 0)
          data.push_back(0);
        else if(val > 1)
          data.push_back(255);
        else
          data.push_back(static_cast<unsigned char>(val * 255));
      };
      add_pixel_data(c.r());
      add_pixel_data(c.g());
      add_pixel_data(c.b());
      data.push_back(255);
    }
  }
  return data;
}
