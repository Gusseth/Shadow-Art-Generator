#include "ShadowGenerator.h"

namespace SAG {
	ShadowGenerator::ShadowGenerator(PNG & image)
	{
		image_ = new PNG(image);
		threshold_ = 0.25;
		invert_ = false;
		alphaThreshold_ = 0.25;
	}

	ShadowGenerator::ShadowGenerator(PNG & image, double threshold, bool invert, double alphaThreshold)
	{
		image_ = new PNG(image);
		threshold_ = threshold;
		invert_ = invert;
		alphaThreshold_ = alphaThreshold;
	}

	ShadowGenerator::~ShadowGenerator()
	{
		delete image_;
		image_ = NULL;
	}

	void ShadowGenerator::Render()
	{
		int width = image_->width();
		int height = image_->height();

		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				HSLAPixel* p = image_->getPixel(x, y);
				if (p->a == 0 || 
					(invert_ && p->a < alphaThreshold_) || (!invert_ && p->a < alphaThreshold_)) {
					if (!invert_) {
						p->l = 1;
					}
					else {
						p->l = 0;
					}
					p->a = 1;
				}
				else {
					if (!invert_) {
						p->l = p->l >= threshold_ ? 0 : 1.0;
					}
					else {
						p->l = p->l >= threshold_ ? 1.0 : 0;
					}
				}
			}
		}

	}

	void ShadowGenerator::RenderToImage(PNG & image)
	{
		image = *image_;
	}

	bool ShadowGenerator::SetThreshold(double threshold)
	{
		threshold_ = threshold;
		return true;
	}
	double ShadowGenerator::GetThreshold() { return threshold_; }

	bool ShadowGenerator::SetInvert(bool invert)
	{
		invert_ = invert;
		return true;
	}
	bool ShadowGenerator::GetInvert() { return invert_; }

}
