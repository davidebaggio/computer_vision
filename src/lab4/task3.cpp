#include "image_func.hpp"
#include "trackbar_callbacks.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./task4.1 <image_path>\n");
		return 1;
	}

	const char *image_path = argv[1];

	int lowThreshold = 50;
	int highThreshold = 150;
	const int maxThreshold = 300;

	cv::Mat original = cv::imread(image_path, cv::IMREAD_COLOR);
	cv::Mat hsv;
	cv::cvtColor(original, hsv, cv::COLOR_BGR2HSV);

	// extract the yellow color part
	cv::Scalar lower_yellow(20, 100, 100);
	cv::Scalar upper_yellow(30, 255, 255);

	cv::Mat mask;
	cv::inRange(hsv, lower_yellow, upper_yellow, mask);
	cv::Mat mask_filtered;
	cv::GaussianBlur(mask, mask, cv::Size(3, 3), 2, 2);
	apply_filter(mask, mask_filtered, DEFKERNEL, median_filter);

	display_image(mask_filtered, "yellow mask");

	cv::Mat result;
	poly_in_hough_circles(original, mask_filtered, result);
	display_image(result, "poly circle with hough circles");

	return 0;
}