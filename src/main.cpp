#include "image_func.hpp"
#include "pixel_transform.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./opencv_test <image_path>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	printf("----------------------------\n");
	const char *image_path = argv[1];
	// display_image(image_path, "original");

	cv::Mat gray_scale_original = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	display_image(gray_scale_original, "Gray scale original");
	cv::Mat negated = apply_transformation(gray_scale_original, negate_transform, DEFPARAM(NONE));
	display_image(negated, "Negate");
	display_image(images_diff(gray_scale_original, negated), "gray-scale/negate difference");

	cv::Mat log = apply_transformation(image_path, log_transform, DEFPARAM(NONE));
	display_image(log, "Log");
	cv::Mat cs_log = apply_transformation(image_path, log_transform, PARAM(96, 32, 160, 224, NONE));
	display_image(cs_log, "Contrast-stretching with log-transform");
	display_image(images_diff(log, cs_log), "Log/Constrast-stretching-Log difference");

	cv::Mat gamma = apply_transformation(image_path, gamma_transform, DEFPARAM(0.04));
	display_image(gamma, "gamma-0.04");

	cv::Mat thresh_127 = apply_transformation(image_path, threshold_transform, DEFPARAM(127));
	display_image(thresh_127, "Threshold-127");

	cv::Mat cs_linear = apply_transformation(image_path, linear_transform, PARAM(96, 32, 160, 224, NONE));
	display_image(cs_linear, "Contrast-stretching");

	cv::Mat original_histogram = image_histogram(gray_scale_original);
	display_image(original_histogram, "original histogram");

	return 0;
}