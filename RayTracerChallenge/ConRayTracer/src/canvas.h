#pragma once

#include "color.h"

class Canvas {
 public:
  Canvas(int width, int height);
  friend std::ostream& operator<<(std::ostream& os, const Canvas& obj);
  int GetWidth() const;
  int GetHeight() const;
  Color PixelAt(int x, int y) const;
  void WritePixel(int x, int y, const Color& color);
  std::string ExportAsPPM(const std::string& file_name) const;

 private:
  int MaxValuesPerLine() const;
  int width_, height_;
  std::vector<Color> pixels_;
};
