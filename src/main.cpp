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

	return 0;
}