#include "Generator.h"


namespace SAG {
	Generator::Generator(PNG& image)
	{
		image_ = new PNG(image);
		invert_ = false;
	}

	Generator::Generator(PNG& image, bool invert)
	{
		image_ = new PNG(image);
		invert_ = invert;
	}
}