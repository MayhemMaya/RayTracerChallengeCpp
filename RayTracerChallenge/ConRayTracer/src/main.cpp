// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <cmath>
#include "utils.h"
#include "tuple.h"
#include "point.h"
#include "vector.h"
#include "environment.h"
#include "projectile.h"
#include "canvas.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"
#include "translation-matrix.h"
#include "scaling-matrix.h"
#include "rotation-matrix.h"
#include "shearing-matrix.h"

int main() {
	int size = 200;
	Canvas c(size, size);
	Color white(1, 1, 1);
	Point p(0, 0, 0);

	float dist = 20;
	int degrees = 15;
	int t = 24;

	for (int i = 0; i < 16; i++)
	{
		TranslationMatrix T(0, dist, 0);
		RotationMatrix R(0, 0, utils::radians(degrees));

		p = T * p;

		for (int j = 0; j < t; j++)
		{
			int x = round(p[0] + size / 2);
			int y = round(p[1]);
			c.WritePixel(x, c.GetHeight() - (y + (size / 2)), white);
			std::cout << p << std::endl;
			p = R * p;
		}
		dist += 20;
		//degrees /= 4;
		//t *= 2;
	}

	utils::ExportFile("clock.ppm", c.ToPPM());

	std::cin.get();
	return 0;
}
