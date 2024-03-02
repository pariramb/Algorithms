#ifndef VECTOR_
#define VECTOR_

#include "declarations.h"

namespace geometry {
class Vector {
 private:
  int64_t coord_x_;
  int64_t coord_y_;

 public:
  int64_t GetX() const;
  int64_t GetY() const;
  Vector(const int64_t, const int64_t);
  Vector(const Point&, const Point&);
  int64_t DoubleModule() const;
  Vector operator-() const;
  Vector operator+() const;
  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(const int64_t);
  Vector& operator/=(const int64_t);
};

Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(const Vector&, const int64_t);
Vector operator*(const int64_t, const Vector&);
Vector operator/(const Vector&, const int64_t);
bool operator==(Vector, Vector);
int64_t ScalarProduct(const Vector&, const Vector&);
int64_t operator^(const Vector&, const Vector&);
}  // namespace geometry
#endif  // VECTOR_
