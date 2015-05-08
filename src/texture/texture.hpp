#pragma once

#include <vector>

#include "type/color.hpp"

class texture {
 public:
  texture(
      unsigned int p_width,
      unsigned int p_height,
      unsigned int p_bytes_per_pixel,
      const char* p_data);

  unsigned int width() const;
  unsigned int height() const;
  unsigned int bytes_per_pixel() const;
  color pixel(double u, double v) const;

 private:
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_bytes_per_pixel;
  std::vector<unsigned char> m_data;
};
