#include "image_func.hpp"
#include "pixel_transform.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: task5 <image_path>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	printf("----------------------------\n");
	const char *image_path = argv[1];

	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
	if (image.empty())
	{
		printf("[ERROR]: Could not open file %s\n", image_path);
		return 1;
	}
	cv::Mat grayscale;
	cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);
	display_image(grayscale, "original");

	cv::Mat avg;
	apply_filter(grayscale, avg, KERNEL3x3(cv::Scalar::all(1)), agv_filter);
	display_image(avg, "Avg filter");

	cv::Mat sobel;
	apply_filter(grayscale, sobel, DEFKERNEL, sobel_filter);
	display_image(sobel, "sobel filter");

	cv::Mat min;
	apply_filter(grayscale, min, DEFKERNEL, min_filter);
	display_image(min, "min filter");

	cv::Mat max;
	apply_filter(grayscale, max, DEFKERNEL, max_filter);
	display_image(max, "max filter");
}