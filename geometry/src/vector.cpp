#include "../vector.h"
#include "../point.h"

namespace geometry {
Vector::Vector(const int64_t x, const int64_t y) : coord_x_(x), coord_y_(y) {
}

Vector operator+(const Vector& vector1, const Vector& vector2) {
  return Vector(vector1.GetX() + vector2.GetX(), vector1.GetY() + vector2.GetY());
}

Vector Vector::operator-() const {
  return Vector(-GetX(), -GetY());
}

Vector Vector::operator+() const {
  return *this;
}

Vector operator-(const Vector& vector1, const Vector& vector2) {
  return Vector(vector1.GetX() - vector2.GetX(), vector1.GetY() - vector2.GetY());
}

Vector operator*(const Vector& vector, const int64_t scalar) {
  return Vector(vector.GetX() * scalar, vector.GetY() * scalar);
}

Vector operator*(const int64_t scalar, const Vector& vector) {
  return (vector * scalar);
}

Vector operator/(const Vector& vector, const int64_t scalar) {
  return Vector(vector.GetX() / scalar, vector.GetY() / scalar);
}

Vector& Vector::operator+=(const Vector& vector) {
  coord_x_ += vector.coord_x_;
  coord_y_ += vector.coord_y_;
  return *this;
}

Vector& Vector::operator-=(const Vector& vector) {
  coord_x_ -= vector.coord_x_;
  coord_y_ -= vector.coord_y_;
  return *this;
}

Vector& Vector::operator*=(const int64_t scalar) {
  coord_x_ *= scalar;
  coord_y_ *= scalar;
  return *this;
}

Vector& Vector::operator/=(const int64_t scalar) {
  coord_x_ /= scalar;
  coord_y_ /= scalar;
  return *this;
}

bool operator==(Vector vector1, Vector vector2) {
  return ((vector1.GetX() == vector2.GetX()) && (vector1.GetY() == vector2.GetY()));
}

int64_t ScalarProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.GetX() * vector_2.GetX() + vector_1.GetY() * vector_2.GetY();
}

int64_t Vector::GetX() const {
  return coord_x_;
}

int64_t Vector::GetY() const {
  return coord_y_;
}

Vector::Vector(const Point& begin, const Point& end)
    : coord_x_(end.GetX() - begin.GetX()), coord_y_(end.GetY() - begin.GetY()) {
}

int64_t operator^(const Vector& vector1, const Vector& vector2) {
  return vector1.GetX() * vector2.GetY() - vector1.GetY() * vector2.GetX();
}
}  // namespace geometry
