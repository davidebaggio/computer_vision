#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./main <image_path>" << std::endl;
		return -1;
	}
	printf("OpenCV version: %s\n", CV_VERSION);
	display_image(argv[1]);

	return 0;
}