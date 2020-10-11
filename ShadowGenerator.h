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
		//ShadowGenerator(PNG& image) : Generator(image) {};
		using Generator::Generator;

		// Creates a generator with initialized values
		ShadowGenerator(PNG & image, double threshold, bool invert = false, double alphaThreshold = 0.25);

		// Destructor, flushes image_
		//~ShadowGenerator() : Generator::~Generator();

		// Renders the image_ within the generator
		void Render();

		// Replaces image with image_ data 
		//void RenderToImage(PNG & image);

		// Sets the threshold value
		bool SetThreshold(double threshold);
		double GetThreshold();

		// Sets the threshold value
		bool SetAlphaThreshold(double alphaThreshold);
		double GetAlphaThreshold();

		// Sets the invert value
		//bool SetInvert(bool invert);
		//bool GetInvert();

	private:
		double threshold_;
		double alphaThreshold_;
	};
}

