#ifndef POLYGON_
#define POLYGON_

#include "declarations.h"

namespace geometry {
class Polygon : public IShape {
 private:
  std::vector<Point> points_;

 public:
  Polygon() = default;
  explicit Polygon(const std::vector<Point>& points);
  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;
  ~Polygon() override;
};
void MakeSides(const std::vector<Point>&, std::vector<Segment>&);
bool OnSide(const std::vector<Segment>, const Point&);
}  // namespace geometry

#endif  // POLYGON_
