#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("[ERROR]: not enough arguments provided.\n\tUsage: task1 <image_path>\n");
		return 1;
	}

	char *file_name = argv[1];
	cv::Mat grayscale = cv::imread(file_name, cv::IMREAD_GRAYSCALE);
	cv::Mat color = cv::imread(file_name, cv::IMREAD_COLOR);

	if (grayscale.empty() || color.empty())
	{
		printf("[ERROR]: Could not open image %s\n", file_name);
		return 1;
	}

	cv::namedWindow("Display Window", cv::WINDOW_GUI_NORMAL);

	cv::imshow("Display Window", grayscale);
	cv::waitKey(0);

	cv::imshow("Display Window", color);
	cv::waitKey(0);
}