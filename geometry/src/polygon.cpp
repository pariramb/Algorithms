#include "../point.h"
#include "../segment.h"
#include "../ray.h"
#include "../polygon.h"

namespace geometry {
Polygon::Polygon(const std::vector<Point>& points) : points_(points) {
}

Polygon& Polygon::Move(const Vector& vector) {
  size_t polygon_size = points_.size();
  for (size_t i = 0; i < polygon_size; ++i) {
    points_[i].Move(vector);
  }
  return *this;
}

void MakeSides(const std::vector<Point>& points, std::vector<Segment>& sides) {
  size_t size_polygon = points.size();
  for (size_t i = 0; i < size_polygon - 1; ++i) {
    sides.emplace_back(Segment(points[i], points[i + 1]));
  }
  sides.emplace_back(Segment(points[size_polygon - 1], points[0]));
}

bool OnSide(const std::vector<Segment> sides, const Point& point) {
  size_t size_polygon = sides.size();
  for (size_t i = 0; i < size_polygon; ++i) {
    if (sides[i].ContainsPoint(point)) {
      return true;
    }
  }
  return false;
}

bool Polygon::ContainsPoint(const Point& point) const {
  std::vector<Segment> sides;
  MakeSides(points_, sides);
  if (OnSide(sides, point)) {
    return true;
  }
  Ray ray(point, Point{1 + point.GetX(), point.GetY()});
  size_t size_polygon = sides.size();
  size_t counter = 0;
  for (size_t i = 0; i < size_polygon; ++i) {
    if (ray.CrossesSegment(sides[i])) {
      bool begin = ray.ContainsPoint(sides[i].GetBegin());
      bool end = ray.ContainsPoint(sides[i].GetEnd());
      bool begin_higher = (sides[i].GetBegin().GetY() > sides[i].GetEnd().GetY());
      if (begin && !end) {
        if (begin_higher) {
          ++counter;
        }
      }
      if (!begin && end) {
        if (!begin_higher) {
          ++counter;
        }
      }
      if (!begin && !end) {
        ++counter;
      }
    }
  }
  return (counter % 2 != 0);
}

bool Polygon::CrossesSegment(const Segment& segment) const {
  std::vector<Segment> sides;
  MakeSides(points_, sides);
  size_t size_polygon = sides.size();
  for (size_t i = 0; i < size_polygon; ++i) {
    if (sides[i].CrossesSegment(segment)) {
      return true;
    }
  }
  return false;
}

Polygon* Polygon::Clone() const {
  return new Polygon(*this);
}

std::string Polygon::ToString() const {
  std::string a = "Polygon(";
  size_t size_polygon = points_.size();
  for (size_t i = 0; i < size_polygon - 1; ++i) {
    a += points_[i].ToString() + ", ";
  }
  a += points_[size_polygon - 1].ToString() + ")";
  return a;
}

Polygon::~Polygon() = default;
}  // namespace geometry
