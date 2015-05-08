#pragma once

class color {
 public:
  color();
  color(double p_r, double p_g, double p_b);
  color operator+(const color& c) const;
  color operator*(double f) const;
  color operator*(const color& c) const;
  color operator/(double f) const;
  double r() const;
  double g() const;
  double b() const;

 private:
  double m_r, m_g, m_b;
};
