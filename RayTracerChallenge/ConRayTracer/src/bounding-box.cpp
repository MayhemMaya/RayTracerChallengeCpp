#include "bounding-box.h"
#include "cube.h"


BoundingBox::BoundingBox()
  : minimum_(Point(-utils::kINFINITY, -utils::kINFINITY, -utils::kINFINITY)),
    maximum_(Point(utils::kINFINITY, utils::kINFINITY, utils::kINFINITY)) {}

BoundingBox::BoundingBox(const Point& minimum, const Point& maximum)
  : minimum_(minimum), maximum_(maximum) {}


Point BoundingBox::GetMinimum() const {
  return minimum_;
}

Point BoundingBox::GetMaximum() const {
  return maximum_;
}

void BoundingBox::SetMinimum(const Point& minimum) {
  minimum_ = minimum;
}

void BoundingBox::SetMaximum(const Point& maximum) {
  maximum_ = maximum;
}

void BoundingBox::merge(const BoundingBox& other) {
  minimum_ = Point(std::min(minimum_[0], other.GetMinimum()[0]),
                   std::min(minimum_[1], other.GetMinimum()[1]),
                   std::min(minimum_[2], other.GetMinimum()[2]));

  maximum_ = Point(std::max(maximum_[0], other.GetMaximum()[0]),
                   std::max(maximum_[1], other.GetMaximum()[1]),
                   std::max(maximum_[2], other.GetMaximum()[2]));
}

void BoundingBox::extend_to_fit(const Point& point) {
  minimum_ = Point(std::min(minimum_[0], point[0]),
                   std::min(minimum_[1], point[1]),
                   std::min(minimum_[2], point[2]));

  maximum_ = Point(std::max(maximum_[0], point[0]),
                   std::max(maximum_[1], point[1]),
                   std::max(maximum_[2], point[2]));
}

BoundingBox BoundingBox::transform(const Matrix4& transform) {
  Point minimum = minimum_;
  Point maximum = maximum_;

  this->extend_to_fit(transform * minimum);

  this->extend_to_fit(transform * Point(minimum[0], minimum[1], maximum[2]));

  this->extend_to_fit(transform * Point(maximum[0], minimum[1], minimum[2]));

  this->extend_to_fit(transform * Point(maximum[0], minimum[1], maximum[2]));

  this->extend_to_fit(transform * Point(minimum[0], maximum[1], minimum[2]));

  this->extend_to_fit(transform * Point(minimum[0], maximum[1], minimum[2]));

  this->extend_to_fit(transform * Point(minimum[0], minimum[1], maximum[2]));

  this->extend_to_fit(transform * maximum);

  return *this;
}

bool BoundingBox::equal(const BoundingBox& other, bool precise) const {
  if (precise) {
    return (
      this->minimum_ == other.GetMinimum() &&
      this->maximum_ == other.GetMaximum()
      );
  }

  return (
    this->minimum_[0] == other.GetMinimum()[0] &&
    this->minimum_[1] == other.GetMinimum()[1] &&
    this->minimum_[2] == other.GetMinimum()[2] &&

    this->maximum_[0] == other.GetMaximum()[0] &&
    this->maximum_[1] == other.GetMaximum()[1] &&
    this->maximum_[2] == other.GetMaximum()[2]
  );
}