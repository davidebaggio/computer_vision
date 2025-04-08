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
	cv::Mat grayscale, edges;
	cv::cvtColor(original, grayscale, cv::COLOR_BGR2GRAY);

	// cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

	cv::Mat thresh = apply_transformation(grayscale, threshold_transform, DEFPARAM(170));
	display_image(thresh, "threshold");
	// cv::medianBlur(grayscale, grayscale, 3);
	// display_image(grayscale, "grayscale");

	TB_args args = {
		.low_th = lowThreshold,
		.high_th = highThreshold,
		.max_th = maxThreshold,
		.img = grayscale,
		.edges = &edges,
		.winname = "Canny",
	};

	// interact_trackbars(on_slide_canny, args);

	cv::Mat result;
	poly_in_hough_circles(original, thresh, result);
	display_image(result, "poly circle with hough lines");

	return 0;
}