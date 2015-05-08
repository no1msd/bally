#include "texture.hpp"

#include <cmath>

texture::texture(
    unsigned int p_width,
    unsigned int p_height,
    unsigned int p_bytes_per_pixel,
    const char* p_data):
    m_width(p_width),
    m_height(p_height),
    m_bytes_per_pixel(p_bytes_per_pixel),
    m_data{
        reinterpret_cast<const unsigned char*>(p_data),
        reinterpret_cast<const unsigned char*>(p_data) +
            p_width * p_height * p_bytes_per_pixel}
{
}

unsigned int texture::width() const {
  return m_width;
}

unsigned int texture::height() const {
  return m_height;
}

unsigned int texture::bytes_per_pixel() const {
  return m_bytes_per_pixel;
}

color texture::pixel(double u, double v) const {
  u -= std::trunc(u);
  v -= std::trunc(v);

  int x = static_cast<int>(u * m_width);
  int y = static_cast<int>(v * m_height);
  int index = (x * m_width + y) * m_bytes_per_pixel;

  return color(
      m_data[index + 0] / 255.0,
      m_data[index + 1] / 255.0,
      m_data[index + 2] / 255.0);
}
