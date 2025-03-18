#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("[ERROR]: not enough arguments provided.\n\tUsage: task5 <image_path>\n");
		return 1;
	}
	const char *file_path = argv[1];
	cv::Mat image = cv::imread(file_path);
	display_image(image, "Image window");
	int c = image.channels();
	printf("image channels: %d\n", c);

	cv::Mat grayscale;
	if (c == 3)
	{
		cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);
	}
	if (c == 4)
	{
		cv::cvtColor(image, grayscale, cv::COLOR_BGRA2GRAY);
	}

	const char *output_path = "./assets/Garden_grayscale.jpg";
	if (!cv::imwrite(output_path, grayscale))
	{
		printf("[ERROR]: Cannot save image to '%s'\n", output_path);
		return 1;
	}

	float range[] = {0, 256}; // the upper boundary is exclusive
	const float *hist_range[] = {range};
	cv::Mat hitsogram = calculate_histogram(grayscale, 256, hist_range);
	display_image(hitsogram, "Histogram of grayscale garden");

	return 0;
}