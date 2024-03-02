#ifndef SEGMENT_
#define SEGMENT_

#include "IShape.h"

namespace geometry {
class Segment : public IShape {
 private:
  Point begin_;
  Point end_;

 public:
  Segment(const Point&, const Point&);
  Point GetBegin() const;
  Point GetEnd() const;
  Segment& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Segment* Clone() const override;
  std::string ToString() const override;
  ~Segment() override;
};

bool IscrossOnOneLine(const Segment&, const Segment&);
bool IscrossLine(const Segment&, const Line&);
}  // namespace geometry

#endif  //  SEGMENT_
