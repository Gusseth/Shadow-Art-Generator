#include "Otsu.h"
#include<cmath>
#include<array>
using namespace std;
using namespace png;

namespace SAG {

	// Otsu's method of monochroming an image. 
	// Unintended effects are: turning your image into a manga, cursed-looking image
	void Otsu::Render()
	{
		makeHistogram();
		int threshold = calculateThreshold();
		
		// Apply pixel changes
		for (int x = 0; x < image_->width(); x++) {
			for (int y = 0; y < image_->height(); y++) {
				HSLAPixel* p = image_->getPixel(x, y);

				if (p->a == 0) {
					// Transparent pixel, make this part of the background
					invert_ ? p->l = 1 : p->l = 0;
					p->a = 1;
					continue;
				}
				if (p->l >= threshold / 255.0) {
					// Pixel is part of the foreground
					invert_ ? p->l = 1 : p->l = 0;
				}
				else {
					// Pixel is part of the background
					invert_ ? p->l = 0 : p->l = 1;
				}
			}
		}
	}

	bool Otsu::makeHistogram()
	{
		// Clear histogram
		for (int& i : histogram) {
			i = 0;
		}

		for (int x = 0; x < image_->width(); x++) {
			for (int y = 0; y < image_->height(); y++) {
				HSLAPixel* p = image_->getPixel(x, y);
				//p->s = 0;

				// Check to make sure the pixel is not transparent
				if (p->a != 0) {
					int rgbMax = round(p->l * 255);	// Converts to a maximum value RGB
					histogram[rgbMax]++;			// Add this pixel to the histogram
					histogramSum += rgbMax;			// Adds the 0-255 value to the sum of the histogram
					totalPixels++;					// Add pixel to total count
				}
			}
		}
		return true;
	}

	int Otsu::calculateThreshold()
	{
		double wB = 0;		// Weight of the background
		double wF = 0;		// Weight of the foreground

		double sumB = 0;
		double varMax = 0;

		int threshold = 0;	// RGB value of the threshold

		// Iterate through the histogram
		for (int t = 0; t < 256; t++) {
			wB += histogram[t];		// Add weight ts of background
			if (wB == 0) continue;

			wF = totalPixels - wB;
			if (wF == 0) break;	// End of the image, all pixels have been added.

			sumB += (double)t * histogram[t];



			double mB = sumB / wB; // Background mean
			double mF = ((double)histogramSum - sumB) / wF;    // Foreground mean

			// Calculate Between Class Variance
			double varBetween = wB * wF * (mB - mF) * (mB - mF);	// Calculate variance

			// Calculates where the maximum between variance is located
			if (varBetween > varMax) {	// If a larger variance is found,
				varMax = varBetween;	// Made this the max...
				threshold = t;			// and the threshold.
			}
		}

		return threshold;
	}
}
