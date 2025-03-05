#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf("Usage: ./resize_img <image_path> <new_width> <new_height>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	printf("----------------------------\n");
	const char *image_path = argv[1];
	int new_width = atoi(argv[2]);
	int new_height = atoi(argv[3]);
	// display_image(image_path, "original");

	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
	cv::Mat resized = cv::Mat::zeros(cv::Size2i(new_width, new_height), image.type());

	cv::resize(image, resized, resized.size(), 0, 0, 1);
	// display_image(resized, "resized");

	std::string s(image_path);
	size_t idx = s.find_last_of('.');
	std::string file_name = s.substr(0, idx);
	std::string file_ext = s.substr(idx);
	file_name += "_resized";
	s = file_name + file_ext;

	cv::imwrite(s, resized);
	printf("Output saved at %s\n", s.c_str());

	return 0;
}