#pragma once

#include <memory>

#include "type/vector.hpp"

class object;

class intersection {
 public:
 intersection();
 intersection(
      const vector& p_point,
      const vector& p_normal,
      std::shared_ptr<object> p_obj);
  bool intersects() const;
  std::shared_ptr<object> obj() const;
  void obj(std::shared_ptr<object> p_object);
  const vector& point() const;
  const vector& normal() const;

 private:
  bool m_intersects;
  vector m_point;
  vector m_normal;
  std::shared_ptr<object> m_obj;
};
