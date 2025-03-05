#ifndef PIXEL_TRANSFORM_HPP
#define PIXEL_TRANSFORM_HPP

#include <opencv2/opencv.hpp>

#define NONE 0

typedef struct ParamSet
{
	uchar basex, basey;
	uchar targetx, targety;
	float param;
} ParamSet;

#define PARAM(basex, basey, targetx, targety, param) \
	(ParamSet) { basex, basey, targetx, targety, param }
#define NOPARAM PARAM(NONE, NONE, NONE, NONE, NONE)
#define DEFPARAM(p) PARAM(0, 0, 255, 255, p)

bool is_default_param(ParamSet param);

// transormation function
uchar negate_transform(const uchar &pixel, ParamSet param);
uchar log_transform(const uchar &pixel, ParamSet param);
uchar gamma_transform(const uchar &pixel, ParamSet param);
uchar threshold_transform(const uchar &pixel, ParamSet param);
uchar linear_transform(const uchar &pixel, ParamSet param);

#endif // PIXEL_TRANSFORM_HPP