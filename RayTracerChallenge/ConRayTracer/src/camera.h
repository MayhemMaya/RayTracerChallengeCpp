#pragma once

#include <cmath>
#include "object.h"
#include "Matrix4.h"
#include "utils.h"

class Camera : public Object {
 public:
   Camera(const std::string& name, int hsize, int vsize, float field_of_view);
   Camera(const std::string& name, int hsize, int vsize, float field_of_view, const Matrix4& transform);
   ~Camera();
   int GetHorizontalSize() const;
   void SetHorizontalSize(int hsize);
   int GetVerticalSize() const;
   void SetVerticalSize(int vsize);
   float GetFieldOfView() const;
   void SetFieldOfView(double field_of_view);
   float GetPixelSize() const;
   float GetHalfWidth() const;
   float GetHalfHeight() const;
   void ListDetails() const override;
   static int GetCount();
   bool operator==(const Object& object) const;
   Camera& operator=(const Object& object);
 private:
   static int camera_count_;
   int hsize_;
   int vsize_;
   float field_of_view_;
   float pixel_size_;
   float half_width_;
   float half_height_;
};
