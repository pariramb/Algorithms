#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include "../line.h"
#include "../ray.h"

namespace geometry {
Ray::Ray(const Point& begin, const Point& end) : begin_(begin), end_(end) {
}

Point Ray::GetBegin() const {
  return begin_;
}

Point Ray::GetEnd() const {
  return end_;
}

Ray& Ray::Move(const Vector& vector) {
  begin_.Move(vector);
  end_.Move(vector);
  return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
  Vector vector1 = Vector(begin_, point);
  Vector vector2 = Vector(begin_, end_);
  if ((vector1 ^ vector2) == 0) {
    return (ScalarProduct(vector1, vector2) >= 0);
  }
  return false;
}

bool Ray::CrossesSegment(const Segment& segment) const {
  Line line(begin_, end_);
  Vector guarding_line(begin_, end_);
  Vector guarding_segment(segment.GetBegin(), segment.GetEnd());
  Vector vector(segment.GetBegin(), begin_);
  if (line.CrossesSegment(segment)) {
    int64_t vproduct1 = (vector ^ guarding_segment);
    int64_t vproduct2 = (guarding_line ^ guarding_segment);
    if (vproduct1 * vproduct2 < 0) {
      return true;
    }
    Vector to_begin = Vector(begin_, segment.GetBegin());
    if (((to_begin ^ guarding_line) == 0) && (ScalarProduct(to_begin, guarding_line) >= 0)) {
      return true;
    }
    Vector to_end = Vector(begin_, segment.GetEnd());
    if (((to_end ^ guarding_line) == 0) && (ScalarProduct(to_end, guarding_line) >= 0)) {
      return true;
    }
  }
  return false;
}

Ray* Ray::Clone() const {
  return new Ray(*this);
}

std::string Ray::ToString() const {
  Vector guarding_vector(begin_, end_);
  return "Ray(" + begin_.ToString() + ", Vector(" +
         std::to_string(guarding_vector.GetX()) + ", " + std::to_string(guarding_vector.GetY()) + "))";
}

Ray::~Ray() = default;
}  // namespace geometry
