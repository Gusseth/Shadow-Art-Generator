#pragma once
#include <iostream>
#include <string>
#include "png/PNG.h"
#include "Generator.h"
using namespace std;
using namespace png;

namespace SAG {
	class ShadowGenerator : public virtual Generator
	{
	public:
		// Creates a generator with default values
		ShadowGenerator(PNG & image);

		// Creates a generator with initialized values
		ShadowGenerator(PNG & image, double threshold, bool invert = false, double alphaThreshold = 0.25);

		// Destructor, flushes image_
		~ShadowGenerator();

		// Renders the image_ within the generator
		void Render();

		// Sets the threshold value
		bool SetThreshold(double threshold);
		double GetThreshold();

		// Sets the threshold value
		bool SetAlphaThreshold(double alphaThreshold);
		double GetAlphaThreshold();

	private:
		double threshold_;
		double alphaThreshold_;
	};
}

