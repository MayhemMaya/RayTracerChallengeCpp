#pragma once

#include "object.h"
#include "color.h"
#include "point.h"
#include "vector.h"

class LightSource : public Object {
public:
  LightSource(std::string name, const ObjectType& type, const Point& position,
                                                       const Color& intensity);
  virtual ~LightSource() = 0;
  void ListDetails() const override;
  Color GetIntensity() const;
  void SetIntensity(const Color& intensity);
  static int GetCount();
  bool operator==(const Object& object) const override;
  LightSource& operator=(const Object& other) override;
private:
  static int light_count_;
  Color intensity_;
};
