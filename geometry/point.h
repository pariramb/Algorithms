#ifndef POINT_
#define POINT_

#include "IShape.h"

namespace geometry {
class Point : public IShape {
 private:
  int64_t coord_x_;
  int64_t coord_y_;

 public:
  Point(const int64_t, const int64_t);
  int64_t GetX() const;
  int64_t GetY() const;
  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Point* Clone() const override;
  std::string ToString() const override;
  ~Point() override;
};
int64_t DoubleDistant(const Point&, const Point&);
Vector operator-(const Point& point1, const Point& point2);
}  // namespace geometry

#endif  // POINT_
