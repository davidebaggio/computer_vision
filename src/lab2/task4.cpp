#include "image_func.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("[ERROR]: not enough arguments provided.\n\tUsage: task4 <kernel_size>\n");
		return 1;
	}
	const char *file_path = "./assets/Garden.jpg";
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

	const char *astronaut_path = "./assets/Astronaut_original.png";
	cv::Mat astronaut = cv::imread(astronaut_path, cv::IMREAD_GRAYSCALE);
	const char *astronaut_corrupted_path = "./assets/Astronaut_salt_pepper.png";
	cv::Mat astronaut_corrupted = cv::imread(astronaut_corrupted_path, cv::IMREAD_GRAYSCALE);
	int kernel_size = atoi(argv[1]);

	cv::Mat astronaut_corrected;
	apply_filter(astronaut_corrupted, astronaut_corrected, KERNELNxN(kernel_size), min_filter);
	display_image(astronaut, "Astro original");
	display_image(astronaut_corrected, "Astro corrected with min filter");

	apply_filter(astronaut_corrupted, astronaut_corrected, KERNELNxN(kernel_size), max_filter);
	display_image(astronaut, "Astro original");
	display_image(astronaut_corrected, "Astro corrected with max filter");

	apply_filter(astronaut_corrupted, astronaut_corrected, KERNELNxN(kernel_size), median_filter);
	display_image(astronaut, "Astro original");
	display_image(astronaut_corrected, "Astro corrected with median filter");

	cv::GaussianBlur(astronaut_corrupted, astronaut_corrected, cv::Size2i(kernel_size, kernel_size), 0);
	display_image(astronaut, "Astro original");
	display_image(astronaut_corrected, "Astro corrected with gaussian filter");

	cv::Mat garden_no_cable;
	apply_filter(grayscale, garden_no_cable, KERNELNxN(kernel_size), min_filter);
	display_image(grayscale, "Garden grayscale original");
	display_image(garden_no_cable, "Garden no cable with min filter");

	// kernel size of 5 is best for this image with max filter
	apply_filter(grayscale, garden_no_cable, KERNELNxN(5), max_filter);
	display_image(grayscale, "Garden grayscale original");
	display_image(garden_no_cable, "Garden no cable with max filter");

	/* apply_filter(grayscale, garden_no_cable, KERNELNxN(kernel_size), median_filter);
	display_image(grayscale, "Garden grayscale original");
	display_image(garden_no_cable, "Garden no cable with median filter"); */

	cv::GaussianBlur(grayscale, garden_no_cable, cv::Size2i(kernel_size, kernel_size), 0);
	display_image(grayscale, "Garden grayscale original");
	display_image(garden_no_cable, "Garden no cable with gaussian filter");

	return 0;
}