#include "image_func.hpp"

std::vector<cv::Mat> check_and_split(const cv::Mat &image)
{
	if (image.channels() != 3)
	{
		return std::vector<cv::Mat>();
	}

	return split_channels(image);
}

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
	char c = (char)cv::waitKey(0);
	printf("Channels for grayscale image: %d\nButton Pressed for closing window: |%c|\n", grayscale.channels(), c);

	cv::imshow("Display Window", color);
	c = (char)cv::waitKey(0);
	printf("Channels for grayscale image: %d\nButton Pressed for closing window: |%c|\n", color.channels(), c);

	std::vector<cv::Mat> splits = check_and_split(color);

	for (size_t i = 0; i < splits.size(); i++)
	{
		cv::imshow("Display Window", splits[i]);
		cv::waitKey(0);
	}
}