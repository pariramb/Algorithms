#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include "../circle.h"

namespace geometry {
Circle::Circle(const Point& point, const int64_t radius) : centre_(point), radius_(radius) {
}

Circle& Circle::Move(const Vector& vector) {
  centre_.Move(vector);
  return *this;
}

int64_t DoubleDistant(const Point& point1, const Point& point2) {
  return (point1.GetX() - point2.GetX()) * (point1.GetX() - point2.GetX()) +
         (point1.GetY() - point2.GetY()) * (point1.GetY() - point2.GetY());
}

bool Circle::ContainsPoint(const Point& point) const {
  int64_t double_distant = DoubleDistant(point, centre_);
  return (double_distant <= radius_ * radius_);
}

int64_t Vector::DoubleModule() const {
  return coord_x_ * coord_x_ + coord_y_ * coord_y_;
}

bool Circle::CrossesSegment(const Segment& segment) const {
  bool begin_inside = ContainsPoint(segment.GetBegin());
  bool end_inside = ContainsPoint(segment.GetEnd());
  if ((begin_inside && !end_inside) || (!begin_inside && end_inside)) {
    return true;
  }
  if (!begin_inside && !end_inside) {
    Vector vector1(centre_, segment.GetBegin());
    Vector vector2(centre_, segment.GetEnd());
    Vector base = vector1 - vector2;
    return (base.DoubleModule() * radius_ * radius_ >= (vector1 ^ vector2) * (vector1 ^ vector2));
  }
  return (((DoubleDistant(centre_, segment.GetBegin()) == radius_ * radius_) ||
           (DoubleDistant(centre_, segment.GetEnd()) == radius_ * radius_)));
}

Circle* Circle::Clone() const {
  return new Circle(*this);
}

std::string Circle::ToString() const {
  return "Circle(" + centre_.ToString() + ", " +
         std::to_string(radius_) + ")";
}

Circle::~Circle() = default;
}  // namespace geometry