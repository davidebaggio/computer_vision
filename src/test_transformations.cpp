#include "image_func.hpp"
#include "pixel_transform.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./test_transformations <image_path>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	printf("----------------------------\n");
	const char *image_path = argv[1];
	// display_image(image_path, "original");

	cv::Mat gray_scale_original = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	display_image(gray_scale_original, "Gray scale original");

	cv::Mat transformed_image;

	transformed_image = apply_transformation(gray_scale_original, negate_transform, DEFPARAM(NONE));
	display_image(transformed_image, "Negate");
	// display_image(images_diff(gray_scale_original, transformed_image), "gray-scale/negate difference");

	transformed_image = apply_transformation(image_path, log_transform, DEFPARAM(NONE));
	display_image(transformed_image, "Log");

	transformed_image = apply_transformation(image_path, log_transform, PARAM(96, 32, 160, 224, NONE));
	display_image(transformed_image, "Contrast-stretching with log-transform");
	// display_image(images_diff(log, transformed_image), "Log/Constrast-stretching-Log difference");

	transformed_image = apply_transformation(image_path, gamma_transform, DEFPARAM(0.04));
	display_image(transformed_image, "gamma-0.04");

	transformed_image = apply_transformation(image_path, threshold_transform, DEFPARAM(127));
	display_image(transformed_image, "Threshold-127");

	transformed_image = apply_transformation(image_path, linear_transform, PARAM(96, 32, 160, 224, NONE));
	display_image(transformed_image, "Contrast-stretching");

	transformed_image = image_histogram(gray_scale_original);
	display_image(transformed_image, "original histogram");

	return 0;
}