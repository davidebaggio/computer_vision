#include "image_func.hpp"
#include "mouse_callbacks.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./task3.4 <image_path>\n");
		return 1;
	}

	const char *image_path = argv[1];
	cv::Mat image = cv::imread(image_path);
	if (image.empty())
	{
		printf("[ERROR]: Image %s not found\n", image_path);
	}
	cv::Mat hsv_image;
	cv::cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);

	interact_display(hsv_image, "Robocup_hsv", on_click_mean_mask);
}