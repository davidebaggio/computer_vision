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

void display_image(cv::Mat image)
{
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

size_t get_num_channels(const char *image_path)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return 0;
	}
	return image.channels();
}

cv::Mat dft_calc(cv::Mat image)
{
	double min, max;
	cv::minMaxLoc(image, &min, &max);
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(image.rows);
	int n = cv::getOptimalDFTSize(image.cols);
	cv::copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
	cv::Mat complex_image;
	cv::merge(planes, 2, complex_image);
	cv::dft(complex_image, complex_image);
	cv::split(complex_image, planes);
	cv::magnitude(planes[0], planes[1], planes[0]);
	cv::Mat mag_image = planes[0];
	mag_image += cv::Scalar::all(1);
	cv::log(mag_image, mag_image);
	mag_image = mag_image(cv::Rect(0, 0, mag_image.cols & -2, mag_image.rows & -2));
	int cx = mag_image.cols / 2;
	int cy = mag_image.rows / 2;
	cv::Mat q0(mag_image, cv::Rect(0, 0, cx, cy));
	cv::Mat q1(mag_image, cv::Rect(cx, 0, cx, cy));
	cv::Mat q2(mag_image, cv::Rect(0, cy, cx, cy));
	cv::Mat q3(mag_image, cv::Rect(cx, cy, cx, cy));
	cv::Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	cv::normalize(mag_image, mag_image, 0, 1, cv::NORM_MINMAX);
	return mag_image;
}

cv::Mat dft_calc(const char *image_path)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	if (image.empty())
	{
		printf("Could not open or find the image\n");
		return cv::Mat();
	}
	return dft_calc(image);
}

cv::Mat profile_of_row(cv::Mat &image, int row)
{
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return cv::Mat();
	}
	if (row < 0 || row >= image.rows)
	{
		std::cout << "Row out of bounds" << std::endl;
		return cv::Mat();
	}
	if (image.channels() > 1)
	{
		printf("Cannot profile row of multi-channel image\n");
		return cv::Mat();
	}

	cv::Mat profile_image = cv::Mat::zeros(255, image.rows, CV_8UC1);
	for (size_t i = 0; i < image.cols; i++)
	{
		uchar pixel_intensity = image.at<uchar>(row, i);
		profile_image.at<uchar>(pixel_intensity, i) = 255;
	}

	return profile_image;
}

cv::Mat profile_of_row(const char *image_path, int row)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return;
	}
	return profile_of_row(image, row);
}

cv::Mat apply_transformation(cv::Mat &image, uchar (*transformation)(const uchar &pixel))
{
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return cv::Mat();
	}
	if (image.channels() > 1)
	{
		printf("Cannot apply transformation to multi-channel image\n");
		return cv::Mat();
	}

	cv::Mat transformed_image = cv::Mat::zeros(image.size(), image.type());

	for (size_t i = 0; i < transformed_image.rows; i++)
	{
		for (size_t j = 0; j < transformed_image.cols; j++)
		{
			transformed_image.at<uchar>(i, j) = transformation(image.at<uchar>(i, j));
		}
	}
	return transformed_image;
}

cv::Mat apply_transformation(const char *image_path, uchar (*transformation)(const uchar &pixel))
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return cv::Mat();
	}
	return apply_transformation(image, transformation);
}