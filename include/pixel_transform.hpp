#ifndef PIXEL_TRANSFORM_HPP
#define PIXEL_TRANSFORM_HPP

#include <opencv2/opencv.hpp>

// transormation function
uchar negate_pixel(const uchar &pixel);
uchar log_transform(const uchar &pixel);

#endif // PIXEL_TRANSFORM_HPP