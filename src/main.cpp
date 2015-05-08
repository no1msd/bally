#include <cmath>
#include <iostream>
#include <vector>
#include <memory>

#include <lodepng.h>

#include "utils.hpp"
#include "scene.hpp"
#include "object/sphere.hpp"
#include "object/plane.hpp"

#include "texture/eyes.h"
#include "texture/eyes2.h"
#include "texture/othereyes.h"

std::vector<std::shared_ptr<sphere>> generate_spheres() {
  double minx = -1300;
  double minz = 100;
  double maxx = 1300;
  double maxz = 1800;
  double minr = 30;
  double maxr = 60;

  std::vector<std::shared_ptr<sphere>> spheres;

  for (int i = 0; i < 300; i++) {
    bool cont;
    do {
      cont = false;

      double randx = get_rand() * (maxx - minx) + minx;
      double randz = get_rand() * (maxz - minz) + minz;
      double randr = get_rand() * (maxr - minr) + minr;
      double randc = get_rand() * (0.5) + 0.2;

      for(auto sphere: spheres)
        if (std::sqrt(std::pow(randx - sphere->origin().x(), 2) +
            std::pow(randz - sphere->origin().z(), 2)) <= randr + sphere->radius())
          cont = true;

      if ((randx - randr < minx) || (randx + randr > maxx) ||
          (randz + randr > maxz) || (std::sqrt(std::pow(randx - 0, 2) +
          std::pow(randz - 180, 2)) < randr + 150))
        cont = true;

      if (!cont)
        spheres.push_back(std::make_shared<sphere>(
            material{color{randc, randc, randc}, 0.2, 20.0, 0.0},
            othereyes,
            vector{randx, -250 + randr, randz},
            randr,
            get_rand() * 360.0));
    } while (cont);
  }

  return spheres;
}


void render(int width, int height, int sample) {
  scene my_scene(width, height);

  // ground
  my_scene.add_object(std::make_shared<plane>(
      material{color{0.6, 0.6, 0.6}, 0.8, 0.0, 0.5},
      vector{0, -250, 470},
      80000,
      axis::y,
      false));

  // blue ball
  my_scene.add_object(std::make_shared<sphere>(
      material{color{0.0, 0.0, 0.8}, 0.2, 20.0, 0.3},
      eyes2_image,
      vector{40, -215, 180},
      35.0,
      200));

  // pink ball
  my_scene.add_object(std::make_shared<sphere>(
      material{color{0.0, 0.0, 0.0}, 0.2, 20.0, 0.3},
      eyes_image,
      vector{-40, -220, 180},
      30.0,
      160));

  // pink hand
  my_scene.add_object(std::make_shared<sphere>(
      material{color{0.88, 0.60, 1.0}, 0.2, 20.0, 0.3},
      nullptr,
      vector{-5, -220, 180},
      3.5,
      0.0));

  // blue hand
  my_scene.add_object(std::make_shared<sphere>(
      material{color{0.58, 0.61, 0.73}, 0.2, 20.0, 0.3},
      nullptr,
      vector{1, -220, 180},
      3.5,
      0.0));

  for (auto sphere: generate_spheres())
    my_scene.add_object(sphere);

  my_scene.add_light({
      vector{400, 0, 500},
      vector{0, 0, 0},
      color{1.0, 1.0, 1.0},
      0.3, 0.3, 60, 0});

  my_scene.add_light({
      vector{-400, 0, 500},
      vector{0, 0, 0},
      color{1.0, 1.0, 1.0},
      0.3, 0.3, 60, 0});

  my_scene.add_light({
      vector{0, 0, 1000},
      vector{0, 0, 0},
      color{1.0, 1.0, 1.0},
      0.3, 0.3, 60, 0});

  my_scene.add_light({
      vector{300, 600, -200},
      vector{0, -220, 180} - vector{300, 600, -200},
      color{1.0, 1.0, 1.0},
      1.0, 0.3, 60, 6});

  auto data = my_scene.render(sample);

  lodepng::encode("bally.png", data, width, height);
}

int main() {
  render(320, 200, 5);
  return 0;
}
