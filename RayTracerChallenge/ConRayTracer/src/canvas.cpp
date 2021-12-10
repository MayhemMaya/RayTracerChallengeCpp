
#include <iostream>
#include <string>
#include <sstream>
#include "canvas.h"
#include "utils.h"

Canvas::Canvas(int width, int height)
    : width_(width), height_(height) {
  if ((width != 0) || (height != 0)) {
    int pixel_count = width * height;
    for (int i = 0; i < pixel_count; i++) {
      pixels_.push_back(Color(0, 0, 0));
    }
  }
}

int Canvas::GetWidth() const { return width_; }
int Canvas::GetHeight() const { return height_; }

std::ostream& operator<<(std::ostream& os, const Canvas& obj) {
  for (int y = 0; y < obj.height_; y++) {
		for (int x = 0; x < obj.width_; x++) {
			os << obj.PixelAt(x, y) << " ";
		}
		os << std::endl;
	}
  return os;
}

Color Canvas::PixelAt(int x, int y) const {
  if ((x >= width_) || (y >= height_)) {
    std::cout << "Canvas index out of range." << std::endl;
    //exit(0);
  }
  int index = width_ * y + x;
  return pixels_[index];
}

void Canvas::WritePixel(int x, int y, const Color& color) {
  if ((x < 0 || y < 0) || (x >= width_ || y >= height_)) {
    std::cout << "Canvas index out of range." << std::endl;
    return;
  }
  int index = width_ * y + x;
  pixels_[index] = color.clamp();
}

int Canvas::MaxValuesPerLine() const {
  return width_ * 3;
}

std::string Canvas::ToPPM() const {
  std::stringstream ppm;
  // Create PPM header
  ppm << "P3\n";
  ppm << width_ << " " << height_ << "\n";
  ppm << "255\n";

  for (int y = 0; y < height_; y++) {
    int values_per_line = 0;
    std::string line = "";
    bool split_line = false;
    for (int x = 0; x < width_; x++) {
      Color pixel = this->PixelAt(x, y);
      for (int i = 0; i < 3; i++)
      {
        line += utils::ToString(utils::clamp(round(pixel[i] * 255), 0, 255));
        if (values_per_line < this->MaxValuesPerLine() - 1) {
          if (line.size() >= 65 && split_line == false) {
            line += "\n";
            split_line = true;
          }
          else line += " ";
        }
        values_per_line++;
      }
    }
    
    ppm << line << '\n';
  }
  ppm << "\n";
  std::cout << "PPM file created successfully." << std::endl;

  return ppm.str();
}