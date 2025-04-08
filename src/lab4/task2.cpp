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
	int highThreshold = 200;
	const int maxThreshold = 300;

	cv::Mat original = cv::imread(image_path, cv::IMREAD_COLOR);
	cv::Mat grayscale, edges;
	cv::cvtColor(original, grayscale, cv::COLOR_BGR2GRAY);

	cv::Mat thresh = apply_transformation(grayscale, threshold_transform, DEFPARAM(220));
	display_image(thresh, "thresholded image");

	TB_args args = {
		.low_th = lowThreshold,
		.high_th = highThreshold,
		.max_th = maxThreshold,
		.img = thresh,
		.edges = &edges,
		.winname = "Canny",
	};

	cv::Canny(args.img, *(args.edges), args.low_th, args.high_th);
	display_image(*(args.edges), args.winname);

	cv::Mat result;
	poly_in_hough_lines(original, *(args.edges), result);

	display_image(result, "polygon between hough lines");

	return 0;
}