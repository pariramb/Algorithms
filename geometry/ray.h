#ifndef RAY_
#define RAY_

#include "IShape.h"

namespace geometry {
class Ray : public IShape {
 private:
  Point begin_;
  Point end_;

 public:
  Ray() = default;
  Ray(const Point&, const Point&);
  Point GetBegin() const;
  Point GetEnd() const;
  Ray& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
  ~Ray() override;
};
}  // namespace geometry

#endif  // RAY_
