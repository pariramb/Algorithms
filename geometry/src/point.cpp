#include "../vector.h"
#include "../point.h"
#include "../segment.h"

namespace geometry {
Point::Point(const int64_t coord_x, const int64_t coord_y) : coord_x_(coord_x), coord_y_(coord_y) {
}

Point& Point::Move(const Vector& vector) {
  coord_x_ += vector.GetX();
  coord_y_ += vector.GetY();
  return *this;
}

bool Point::ContainsPoint(const Point& point) const {
  return ((coord_x_ == point.coord_x_) && (coord_y_ == point.coord_y_));
}

bool Point::CrossesSegment(const Segment& segment) const {
  Vector vector1(segment.GetBegin(), *this);
  Vector vector2(segment.GetEnd(), *this);
  if ((vector1 ^ vector2) == 0) {
    if (ScalarProduct(vector1, vector2) <= 0) {
      return true;
    }
  }
  return false;
}

Point* Point::Clone() const {
  return new Point(*this);
}

int64_t Point::GetX() const {
  return coord_x_;
}

int64_t Point::GetY() const {
  return coord_y_;
}

std::string Point::ToString() const {
  return "Point(" + std::to_string(coord_x_) + ", " + std::to_string(coord_y_) + ")";
}

Vector operator-(const Point& point1, const Point& point2) {
  return Vector(point1.GetX() - point2.GetX(), point1.GetY() - point2.GetY());
}

Point::~Point() = default;
}  // namespace geometry
