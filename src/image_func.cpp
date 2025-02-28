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