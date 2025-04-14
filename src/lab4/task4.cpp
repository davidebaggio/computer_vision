#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./task4.1 <image_path>\n");
		return 1;
	}

	const char *image_path = argv[1];
	cv::Mat original = cv::imread(image_path, cv::IMREAD_COLOR);

	display_image(original, "original");

	cv::Mat segmented;
	segment_sky(original, segmented);
	display_image(segmented, "segmented hsv");

	segment_sky_with_kmeans(original, segmented);
	display_image(segmented, "segmented kmeans k=5");

	return 0;
}