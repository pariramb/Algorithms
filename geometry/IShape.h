#ifndef ISHAPE_
#define ISHAPE_

#include "declarations.h"

namespace geometry {
class IShape {
 public:
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = 0;
};
}  // namespace geometry

#endif  // ISHAPE_
