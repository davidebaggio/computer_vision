#include "image_filters.hpp"

void agv_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	float kernel_sum = 0;
	for (size_t i = 0; i < kernel.rows; i++)
	{
		for (size_t j = 0; j < kernel.cols; j++)
		{
			kernel_sum += kernel.at<float>(i, j);
		}
	}
	for (size_t i = 0; i < kernel.rows; i++)
	{
		for (size_t j = 0; j < kernel.cols; j++)
		{
			kernel.at<float>(i, j) /= kernel_sum;
		}
	}

	cv::filter2D(src, dst, -1, kernel);
}

void linear_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	cv::filter2D(src, dst, -1, kernel);
}

void sobel_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	cv::Mat grad_x, grad_y;
	cv::Mat abs_x, abs_y;
	cv::Sobel(src, grad_x, CV_16S, 1, 0, kernel.rows, 1, 0, cv::BORDER_DEFAULT);
	cv::Sobel(src, grad_y, CV_16S, 0, 1, kernel.rows, 1, 0, cv::BORDER_DEFAULT);

	cv::convertScaleAbs(grad_x, abs_x);
	cv::convertScaleAbs(grad_y, abs_y);

	cv::addWeighted(abs_x, 0.5, abs_y, 0.5, 0, dst);
}

void mean_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	dst = cv::Mat::zeros(cv::Size2i(src.cols, src.rows), src.type());
	int deltay = kernel.rows / 2;
	int deltax = kernel.cols / 2;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uint sum = 0;
			uint used_size = 0;
			for (int k = -deltay; k <= deltay; k++)
			{
				for (int l = -deltax; l <= deltax; l++)
				{
					if (i + k < 0 || i + k >= src.rows || j + l < 0 || j + l >= src.cols)
						continue;
					sum += src.at<uchar>(i + k, j + l);
					used_size++;
				}
			}
			dst.at<uchar>(i, j) = sum / used_size;
		}
	}
}

void min_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	dst = cv::Mat::zeros(cv::Size2i(src.cols, src.rows), src.type());
	int deltay = kernel.rows / 2;
	int deltax = kernel.cols / 2;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar min = UCHAR_MAX;
			for (int k = -deltay; k <= deltay; k++)
			{
				for (int l = -deltax; l <= deltax; l++)
				{
					if (i + k < 0 || i + k >= src.rows || j + l < 0 || j + l >= src.cols)
						continue;
					if (src.at<uchar>(i + k, j + l) < min)
						min = src.at<uchar>(i + k, j + l);
				}
			}
			dst.at<uchar>(i, j) = min;
		}
	}
}
void max_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	dst = cv::Mat::zeros(cv::Size2i(src.cols, src.rows), src.type());
	int deltay = kernel.rows / 2;
	int deltax = kernel.cols / 2;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar max = 0;
			for (int k = -deltay; k <= deltay; k++)
			{
				for (int l = -deltax; l <= deltax; l++)
				{
					if (i + k < 0 || i + k >= src.rows || j + l < 0 || j + l >= src.cols)
						continue;
					if (src.at<uchar>(i + k, j + l) > max)
						max = src.at<uchar>(i + k, j + l);
				}
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}
void median_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel)
{
	dst = cv::Mat::zeros(cv::Size2i(src.cols, src.rows), src.type());
	int deltay = kernel.rows / 2;
	int deltax = kernel.cols / 2;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			std::vector<uchar> pixels;
			for (int k = -deltay; k <= deltay; k++)
			{
				for (int l = -deltax; l <= deltax; l++)
				{
					if (i + k < 0 || i + k >= src.rows || j + l < 0 || j + l >= src.cols)
						continue;
					pixels.push_back(src.at<uchar>(i + k, j + l));
				}
			}
			std::sort(pixels.begin(), pixels.end());
			if (pixels.size() % 2 != 0)
				dst.at<uchar>(i, j) = pixels.at(pixels.size() / 2);
			else
				dst.at<uchar>(i, j) = (pixels.at(pixels.size() / 2) + pixels.at(pixels.size() / 2 + 1)) / 2;
		}
	}
}
