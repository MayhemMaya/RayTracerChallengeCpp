#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#include <vector>
#include "color.h"

class Canvas {
 public:
  Canvas(int width, int height);
  ~Canvas();
  friend std::ostream& operator<<(std::ostream& os, const Canvas& obj);
  int GetWidth() const;
  int GetHeight() const;
  Color& PixelAt(int x, int y) const;
  void WritePixel(int x, int y, const Color& color);
  std::string ToPPM() const;

 private:
  int MaxValuesPerLine() const;
  int width_, height_;
  std::vector<Color*> pixels_;
};

#endif // CANVAS_H
