#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include "../line.h"

namespace geometry {
Point Line::GetBegin() const {
  return begin_;
}

Point Line::GetEnd() const {
  return end_;
}

Line::Line(const Point& begin, const Point& end)
    : begin_(begin)
    , end_(end)
    , a_(begin.GetY() - end.GetY())
    , b_(end.GetX() - begin.GetX())
    , c_(-a_ * begin.GetX() - b_ * begin.GetY()) {
}

int64_t Line::GetA() const {
  return a_;
}

int64_t Line::GetB() const {
  return b_;
}

int64_t Line::GetC() const {
  return c_;
}

Line& Line::Move(const Vector& vector) {
  begin_.Move(vector);
  end_.Move(vector);
  *this = Line(begin_, end_);
  return *this;
}

bool Line::ContainsPoint(const Point& point) const {
  Vector vector1(begin_, point);
  Vector vector2(end_, point);
  return ((vector1 ^ vector2) == 0);
}

bool Line::CrossesSegment(const Segment& segment) const {
  Point begin = segment.GetBegin();
  Point end = segment.GetEnd();
  int64_t sign_temp_1 = a_ * end.GetX() + b_ * end.GetY() + c_;
  int64_t sign_temp_2 = a_ * begin.GetX() + b_ * begin.GetY() + c_;
  return (sign_temp_2 * sign_temp_1 <= 0);
}

Line* Line::Clone() const {
  return new Line(*this);
}

std::string Line::ToString() const {
  return "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
}

Line::~Line() = default;
}  // namespace geometry
