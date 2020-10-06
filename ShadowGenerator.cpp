#include "ShadowGenerator.h"

namespace SAG {

	// Creates a generator with default values
	ShadowGenerator::ShadowGenerator(PNG & image)
	{
		image_ = new PNG(image);
		threshold_ = 0.25;
		invert_ = false;
		alphaThreshold_ = 0.25;
	}

	// Creates a generator with initialized values
	ShadowGenerator::ShadowGenerator(PNG & image, double threshold, bool invert, double alphaThreshold)
	{
		image_ = new PNG(image);
		threshold_ = threshold;
		invert_ = invert;
		alphaThreshold_ = alphaThreshold;
	}

	// Destructor, flushes image_
	ShadowGenerator::~ShadowGenerator()
	{
		delete image_;
		image_ = NULL;
	}

	// Renders the image_ within the generator
	void ShadowGenerator::Render()
	{
		int width = image_->width();
		int height = image_->height();

		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				HSLAPixel* p = image_->getPixel(x, y);	// Gets pixel

				if (							// If this is a...
					p->a == 0 ||				// Fully transparent pixel
					(p->a < alphaThreshold_))	// or a transparent pixel under the threshold...
				{								// Then this pixel is part of the background
					invert_ ? 
						p->l = 0 :	// Makes the background black under invert mode
						p->l = 1;	// Make the backround white under normal mode

					p->a = 1;	// Make pixel fully opaque
				}
				else {
					// Foreground/Background separation
					if (!invert_) {
						// Under normal mode,
						p->l = p->l >= threshold_ ? 
							0 :		// Anything above the threshold is black
							1.0;	// while anything below is white
					}
					else {
						// Under invert mode,
						p->l = p->l >= threshold_ ? 
							1.0 :	// Anything above the threshold is white
							0;		// while anything below is black
					}
				}
			}
		}

	}

	// Replaces image with image_ data 
	void ShadowGenerator::RenderToImage(PNG & image)
	{
		image = *image_;
	}

	// Sets the threshold value
	bool ShadowGenerator::SetThreshold(double threshold)
	{
		threshold_ = threshold;
		return true;
	}

	// Returns threshold value
	double ShadowGenerator::GetThreshold() { return threshold_; }

	// Sets the alpha threshold value
	bool ShadowGenerator::SetAlphaThreshold(double alphaThreshold)
	{
		alphaThreshold_ = alphaThreshold;
		return true;
	}

	// Returns alpha threshold value
	double ShadowGenerator::GetAlphaThreshold() { return alphaThreshold_; }

	// Sets the invert value
	bool ShadowGenerator::SetInvert(bool invert)
	{
		invert_ = invert;
		return true;
	}

	// Returns invert value
	bool ShadowGenerator::GetInvert() { return invert_; }

}
