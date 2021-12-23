
#include "environment.h"

Environment::Environment(const Vector& gravity, const Vector& wind)
    : gravity_(gravity), wind_(wind) {}

Vector Environment::GetGravity() const { return gravity_; }
Vector Environment::GetWind() const { return wind_; }