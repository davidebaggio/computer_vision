#include "image_func.hpp"
#include "pixel_transform.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./main <image_path>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	display_image(argv[1]);
	// display_image(dft_calc(argv[1]));
	// profile_of_row(argv[1], 500);
	display_image(apply_transformation(argv[1], negate_pixel));
	display_image(apply_transformation(argv[1], log_transform));
	return 0;
}