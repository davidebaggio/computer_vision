#include "image_func.hpp"
#include "pixel_transform.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./test_filters <image_path>\n");
		return 1;
	}
	printf("\nOpenCV version: %s\n", CV_VERSION);
	printf("----------------------------\n");
	const char *image_path = argv[1];
	// display_image(image_path, "original");

	cv::Mat gray_scale_original = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	display_image(gray_scale_original, "Gray scale original");

	cv::Mat agv_image;
	apply_filter(gray_scale_original, agv_image, cv::Mat(3, 3, CV_32F, cv::Scalar::all(1)), agv_filter);
	display_image(agv_image, "avg filter image");

	cv::Mat laplacian;
	apply_filter(gray_scale_original, laplacian, KERNEL3x3(laplacian_terms), linear_filter);
	display_image(laplacian, "laplacian image");
	apply_filter(gray_scale_original, laplacian, KERNEL3x3(laplacian_inv_terms), linear_filter);
	display_image(laplacian, "laplacian image");
	apply_filter(gray_scale_original, laplacian, KERNEL3x3(laplacian_ext_terms), linear_filter);
	display_image(laplacian, "laplacian image");
	apply_filter(gray_scale_original, laplacian, KERNEL3x3(laplacian_ext_inv_terms), linear_filter);
	display_image(laplacian, "laplacian image");

	cv::Mat gaussian = gaussian_noise(gray_scale_original, 0, 50);
	display_image(gaussian, "gaussian noise image");

	cv::Mat corrected_image;
	apply_filter(gaussian, corrected_image, DEFKERNEL, mean_filter);
	display_image(corrected_image, "corrected image");

	cv::Mat salt = salt_noise(gray_scale_original, 0.05);
	display_image(salt, "salt noise image");

	apply_filter(salt, corrected_image, DEFKERNEL, mean_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(salt, corrected_image, DEFKERNEL, min_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(salt, corrected_image, DEFKERNEL, max_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(salt, corrected_image, DEFKERNEL, median_filter);
	display_image(corrected_image, "corrected image");

	cv::Mat pepper = pepper_noise(gray_scale_original, 0.05);
	display_image(pepper, "pepper noise image");

	apply_filter(pepper, corrected_image, DEFKERNEL, mean_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(pepper, corrected_image, DEFKERNEL, min_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(pepper, corrected_image, DEFKERNEL, max_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(pepper, corrected_image, DEFKERNEL, median_filter);
	display_image(corrected_image, "corrected image");

	cv::Mat salt_pepper = salt_pepper_noise(gray_scale_original, 0.05);
	display_image(salt_pepper, "salt_pepper noise image");

	apply_filter(salt_pepper, corrected_image, DEFKERNEL, mean_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(salt_pepper, corrected_image, DEFKERNEL, min_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(salt_pepper, corrected_image, DEFKERNEL, max_filter);
	display_image(corrected_image, "corrected image");

	apply_filter(salt_pepper, corrected_image, DEFKERNEL, median_filter);
	display_image(corrected_image, "corrected image");

	return 0;
}