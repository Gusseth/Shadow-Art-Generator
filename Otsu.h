#pragma once
#include <iostream>
#include <string>
#include "png/PNG.h"
#include "Generator.h"
using namespace std;
using namespace png;

namespace SAG {
	class Otsu : public virtual Generator
	{
	public:
		using Generator::Generator;

		// Runs the 'Otsu's method' algorithm
		void Render();

	private:
		// Fills histogram array with the luminance magnitude 
		bool makeHistogram();

		// Returns the threshold of the image to partition background from foreground
		// according to Otsu's Method
		int calculateThreshold();

		int histogram[256] = {};	// Grayscale histogram of all pixels in RGB
		int histogramSum = 0;		// Sum of luminance inside the histogram
		int totalPixels = 0;		// Total number of pixels in the image
		//int threshold = 0;
	};
}

