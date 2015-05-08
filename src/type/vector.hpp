#pragma once

#include "axis.hpp"

class vector {
 public:
  vector();
  vector(double p_x, double p_y, double p_z);
  void normalize();
  double abs() const;
  void rotate(double angle, axis rotation_axis);
  vector& operator=(const vector& v);
  vector operator+(const vector& v) const;
  vector operator-(const vector& v) const;
  vector operator%(const vector& v) const;
  vector operator*(double f) const;
  vector operator/(double f) const;
  double operator*(const vector& v) const;
  double x() const;
  double y() const;
  double z() const;

 private:
  double m_x, m_y, m_z;
};
