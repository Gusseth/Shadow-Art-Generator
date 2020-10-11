#pragma once
#include "png/PNG.h"
#include <iostream>
#include <string>
#include "png/PNG.h"
using namespace std;
using namespace png;

namespace SAG {
	class Generator
	{
	public:
		Generator() { image_ = NULL; invert_ = NULL; }

		Generator(PNG& image);

		Generator(PNG& image, bool invert);

		~Generator() { delete image_; image_ = NULL; }

		// Renders the image_ within the generator
		virtual void Render() {}

		// Replaces image with image_ data 
		void RenderToImage(PNG& image) {
			image = *image_;
		}

		// Sets the invert value
		bool SetInvert(bool invert) {
			invert_ = invert;
		}
		bool GetInvert() { return invert_; }
	protected:
		PNG* image_;
		bool invert_;
	};
}
