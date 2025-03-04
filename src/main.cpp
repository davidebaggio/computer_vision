#include "image_func.hpp"
#include "pixel_transform.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./main <image_path>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	printf("----------------------------\n");
	display_image(argv[1], "original");

	display_image(apply_transformation(argv[1], negate_pixel, NOPARAM), "Negate");
	display_image(apply_transformation(argv[1], log_transform, PARAM(0, 0, 255, 255, NONE)), "Log");
	display_image(apply_transformation(argv[1], gamma_transform, DEFPARAM(0.04)), "gamma-0.04");
	display_image(apply_transformation(argv[1], gamma_transform, PARAM(96, 32, 160, 224, 0.04)), "Contrast-stretching with gamma-0.04");
	display_image(apply_transformation(argv[1], threshold_transform, DEFPARAM(127)), "Threshold-127");
	display_image(apply_transformation(argv[1], linear_transform, PARAM(96, 32, 160, 224, NONE)), "Contrast-stretching");
	display_image(apply_transformation(argv[1], log_transform, PARAM(96, 32, 160, 224, NONE)), "Contrast-stretching with log-transform");
	return 0;
}