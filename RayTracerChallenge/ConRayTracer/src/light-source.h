#pragma once

#include "object.h"
#include "color.h"
#include "point.h"
#include "vector.h"

class LightSource : public Object {
public:
  LightSource(const std::string& name, const ObjectType& type, const Point& position,
                                                       const Color& intensity);
  virtual ~LightSource() = 0;
  //void ListDetails() const override;
  Color GetIntensity() const;
  void SetIntensity(const Color& intensity);
  static int GetCount();
  bool operator==(const Object& object) override;
  //LightSource& operator=(const Object& other) override;
protected:
  static int light_count_;
  Color intensity_;
};
