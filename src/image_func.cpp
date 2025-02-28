#include "image_func.hpp"

void display_image(const char *image_path)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return;
	}
	printf("Image size: %d x %d\n", image.cols, image.rows);
	cv::namedWindow("Display window", cv::WINDOW_GUI_NORMAL);
	printf("Window created\n");
	cv::imshow("Display window", image);
	cv::waitKey(0);
}