#include "pixel_transform.hpp"

uchar negate_pixel(const uchar &pixel)
{
	return 255 - pixel;
}

uchar log_transform(const uchar &pixel)
{
	return (uchar)(((float)255 / log(256)) * log(1 + pixel));
}