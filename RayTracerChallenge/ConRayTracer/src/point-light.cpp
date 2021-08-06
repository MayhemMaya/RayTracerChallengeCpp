#include "point-light.h"
#include "point.h"
#include "color.h"

PointLight::PointLight(const Point& position, const Color& intensity)
    : LightSource("pointlight", position, intensity) {
}