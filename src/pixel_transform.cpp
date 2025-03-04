#include "pixel_transform.hpp"

bool is_default_param(ParamSet param)
{
	if (param.basex != 0 || param.basey != 0 || param.targetx != 255 || param.targety != 255)
		return false;
	else
		return true;
}

uchar negate_pixel(const uchar &pixel, ParamSet param)
{
	(void)param;
	return (uchar)(255 - pixel);
}

uchar log_transform(const uchar &pixel, ParamSet param)
{
	if (pixel < param.basex)
	{
		printf("Invalid base point for function log_transform\n");
	}
	uchar gapy = param.targety - param.basey;
	uchar gapx = param.targetx - param.basex;
	return param.basey + (uchar)(((float)gapy / log(gapx + 1)) * log(1 + pixel - param.basex));
}

// TODO: add support for the non continous function gamma
uchar gamma_transform(const uchar &pixel, ParamSet param)
{
	if (pixel < param.basex)
	{
		printf("Invalid base point for function gamma_transform\n");
	}
	uchar gapy = param.targety - param.basey;
	return param.basey + (uchar)((pow((float)gapy, 1 - param.param)) * pow((float)(pixel - param.basex), param.param));
}

uchar threshold_transform(const uchar &pixel, ParamSet param)
{
	if (param.param < NONE || param.param > 255)
	{
		printf("Invalid parameter for function threshold_transform\n");
		return 0;
	}
	return (pixel > (uchar)param.param) ? 255 : 0;
}

uchar linear_transform(const uchar &pixel, ParamSet param)
{
	if (pixel < param.basex || pixel > param.targetx)
	{
		printf("Invalid base or target point for function linear_transform\n");
	}
	return param.basey + (uchar)((float)(param.targety - param.basey) / (param.targetx - param.basex) * (pixel - param.basex));
}