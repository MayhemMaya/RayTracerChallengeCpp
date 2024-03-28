#pragma once

#include "object.h"
#include "color.h"
#include "point.h"
#include "vector.h"

class LightSource : public Object {
public:
  LightSource(const std::string& name, const ObjectType& type, const Point& position,
                                                       const Color& intensity);
  virtual ~LightSource() override = 0;
  void ListDetails() const override final;
  Color GetIntensity() const;
  void SetIntensity(const Color& intensity);
  bool operator==(const Object& object) const override;
  LightSource& operator=(const Object& other) override;
protected:
  Color intensity_;
};
