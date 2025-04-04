#include "mouse_callbacks.hpp"

void means(const cv::Mat &img, int *means, int x, int y, int size)
{
	int kernel = size / 2;
	// mean of 9x9 neighbors bgr pixels
	for (int i = -kernel; i <= kernel; i++)
	{
		for (int j = -kernel; j <= kernel; j++)
		{
			if (y + i >= 0 && y + i < img.rows && x + j >= 0 && x + j < img.cols)
			{
				means[0] += img.at<cv::Vec3b>(y + i, x + j)[0];
				means[1] += img.at<cv::Vec3b>(y + i, x + j)[1];
				means[2] += img.at<cv::Vec3b>(y + i, x + j)[2];
			}
		}
	}
	means[0] /= (size * size);
	means[1] /= (size * size);
	means[2] /= (size * size);
}

void on_click(int event, int x, int y, int flags, void *userdata)
{
	(void)flags;
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		printf("Pixel: (%d, %d)\n", x, y);
		cv::Mat *img = (cv::Mat *)userdata;
		cv::Vec3b color = img->at<cv::Vec3b>(y, x);
		printf("BGR: (%d, %d, %d)\n", (int)color[0], (int)color[1], (int)color[2]);
	}
}

void on_click_mean(int event, int x, int y, int flags, void *userdata)
{
	(void)flags;
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		printf("Pixel: (%d, %d)\n", x, y);
		cv::Mat *img = (cv::Mat *)userdata;
		cv::Vec3b color = img->at<cv::Vec3b>(y, x);
		int m[3] = {0, 0, 0};
		means(*img, m, x, y, 9);
		printf("Mean BGR: (%d, %d, %d)\n", (int)m[0], (int)m[1], (int)m[2]);
	}
}

void on_click_mean_mask(int event, int x, int y, int flags, void *userdata)
{
	(void)flags;
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		int T = 20;
		printf("Pixel: (%d, %d)\n", x, y);
		cv::Mat *img = (cv::Mat *)userdata;
		cv::Vec3b color = img->at<cv::Vec3b>(y, x);
		int m[3] = {0, 0, 0};
		means(*img, m, x, y, 9);

		cv::Mat mask = cv::Mat::zeros(img->rows, img->cols, CV_8UC1);
		for (int i = 0; i < img->rows; i++)
		{
			for (int j = 0; j < img->cols; j++)
			{
				cv::Vec3b color = img->at<cv::Vec3b>(i, j);
				if (abs(color[0] - m[0]) < T && abs(color[1] - m[1]) < T && abs(color[2] - m[2]) < T)
				{
					mask.at<uchar>(i, j) = 255;
				}
			}
		}

		cv::imshow("mask", mask);
		cv::waitKey(0);
	}
}

void on_click_mean_mask_on_original(int event, int x, int y, int flags, void *userdata)
{
	(void)flags;
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		int T = 40;
		printf("Pixel: (%d, %d)\n", x, y);
		cv::Mat *img = (cv::Mat *)userdata;
		cv::Vec3b color = img->at<cv::Vec3b>(y, x);
		int m[3] = {0, 0, 0};
		means(*img, m, x, y, 9);

		cv::Mat mask = img->clone();
		for (int i = 0; i < img->rows; i++)
		{
			for (int j = 0; j < img->cols; j++)
			{
				cv::Vec3b color = img->at<cv::Vec3b>(i, j);
				if (abs(color[0] - m[0]) < T && abs(color[1] - m[1]) < T && abs(color[2] - m[2]) < T)
				{
					mask.at<cv::Vec3b>(i, j) = cv::Vec3b(92, 37, 201);
				}
			}
		}

		cv::imshow("mask on original", mask);
		cv::waitKey(0);
	}
}