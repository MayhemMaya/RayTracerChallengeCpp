#pragma once

#include "tuple.h"

class MockTuple : public Tuple {
 public:
   MockTuple();
   MockTuple(float x, float y, float z, float w);
   MockTuple operator+(const MockTuple& other) const;
   bool operator == (const Tuple& other) const override;
   MockTuple operator - (const MockTuple& other) const;
   MockTuple operator - () const;
   MockTuple operator * (const float& scalar) const;
   MockTuple operator / (const float& scalar) const;
};
