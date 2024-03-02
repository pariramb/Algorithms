#ifndef LINE_
#define LINE_

#include "IShape.h"

namespace geometry {
class Line : public IShape {
 private:
  Point begin_;
  Point end_;
  int64_t a_, b_, c_;

 public:
  Line() = default;
  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;
  Point GetBegin() const;
  Point GetEnd() const;
  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Line* Clone() const override;
  std::string ToString() const override;
  Line(const Point&, const Point&);
  ~Line() override;
};
}  // namespace geometry

#endif  // LINE_
