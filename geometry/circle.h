#ifndef CIRCLE_
#define CIRCLE_

#include "IShape.h"

namespace geometry {
class Circle : public IShape {
 private:
  Point centre_;
  int64_t radius_;

 public:
  Circle() = default;
  Circle(const Point&, const int64_t);
  Circle& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
  ~Circle() override;
};
}  // namespace geometry

#endif  // CIRCLE_
