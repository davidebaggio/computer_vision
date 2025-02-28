#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./main <image_path>\n");
		return 1;
	}
	printf("OpenCV version: %s\n", CV_VERSION);
	display_image(argv[1]);
	// display_image(dft_calc(argv[1]));

	return 0;
}