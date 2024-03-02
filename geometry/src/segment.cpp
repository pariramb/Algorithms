#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include "../line.h"

namespace geometry {

Segment::Segment(const Point& point1, const Point& point2) : begin_(point1), end_(point2) {
}

Point Segment::GetBegin() const {
  return begin_;
}

Point Segment::GetEnd() const {
  return end_;
}

Segment& Segment::Move(const Vector& vector) {
  begin_.Move(vector);
  end_.Move(vector);
  return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
  Vector vector1(begin_, point);
  Vector vector2(end_, point);
  if ((vector1 ^ vector2) == 0) {
    return (ScalarProduct(vector1, vector2) <= 0);
  }
  return false;
}

bool IscrossLine(const Segment& segment, const Line& line) {
  Point begin = segment.GetBegin();
  Point end = segment.GetEnd();
  int64_t sign_temp_1 = line.GetA() * end.GetX() + line.GetB() * end.GetY() + line.GetC();
  int64_t sign_temp_2 = line.GetA() * begin.GetX() + line.GetB() * begin.GetY() + line.GetC();
  return (sign_temp_2 * sign_temp_1 <= 0);
}

bool IscrossOnOneLine(const Segment& segment1, const Segment& segment2) {
  if (segment1.GetEnd().GetX() - segment1.GetBegin().GetX() != 0) {
    int64_t min_1 = std::min(segment1.GetBegin().GetX(), segment1.GetEnd().GetX());
    int64_t min_2 = std::min(segment2.GetBegin().GetX(), segment2.GetEnd().GetX());
    int64_t max_1 = std::max(segment1.GetBegin().GetX(), segment1.GetEnd().GetX());
    int64_t max_2 = std::max(segment2.GetBegin().GetX(), segment2.GetEnd().GetX());
    int64_t max_coord_x = std::max(max_1, max_2);
    int64_t min_coord_x = std::min(min_1, min_2);
    return ((max_coord_x - min_coord_x) <= std::abs(segment1.GetBegin().GetX() - segment1.GetEnd().GetX()) +
                                               std::abs(segment2.GetBegin().GetX() - segment2.GetEnd().GetX()));
  }
  int64_t min_1 = std::min(segment1.GetBegin().GetY(), segment1.GetEnd().GetY());
  int64_t min_2 = std::min(segment2.GetBegin().GetY(), segment2.GetEnd().GetY());
  int64_t max_1 = std::max(segment1.GetBegin().GetY(), segment1.GetEnd().GetY());
  int64_t max_2 = std::max(segment2.GetBegin().GetY(), segment2.GetEnd().GetY());
  int64_t max_coord_y = std::max(max_1, max_2);
  int64_t min_coord_y = std::min(min_1, min_2);
  return ((max_coord_y - min_coord_y) <= std::abs(segment1.GetBegin().GetY() - segment1.GetEnd().GetY()) +
                                             std::abs(segment2.GetBegin().GetY() - segment2.GetEnd().GetY()));
}

bool Segment::CrossesSegment(const Segment& segment) const {
  Line line1(begin_, end_);
  Line line2(segment.begin_, segment.end_);
  bool cross_line1 = IscrossLine(segment, line1);
  bool cross_line2 = IscrossLine(*this, line2);
  if (!cross_line1 || !cross_line2) {
    return false;
  }
  Point begin = segment.begin_;
  Point end = segment.end_;
  bool belong_line1_end = (line1.GetA() * end.GetX() + line1.GetB() * end.GetY() + line1.GetC() == 0);
  bool belong_line1_begin = (line1.GetA() * begin.GetX() + line1.GetB() * begin.GetY() + line1.GetC() == 0);
  if (belong_line1_begin && belong_line1_end) {
    return IscrossOnOneLine(*this, segment);
  }
  return true;
}

Segment* Segment::Clone() const {
  return new Segment(*this);
}

std::string Segment::ToString() const {
  return "Segment(" + begin_.ToString() + ", " + end_.ToString() + ")";
}

Segment::~Segment() = default;
}  // namespace geometry
