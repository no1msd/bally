#include "utils.hpp"

#include <random>

double get_rand() {
  static std::mt19937 mt(18); // fix seed for deterministic randomness :)
  std::uniform_real_distribution<double> dist(0, 1);
  return dist(mt);
}
