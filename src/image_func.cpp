#include "image_func.hpp"

void display_image(const char *image_path, const char *window_name)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);

	display_image(image, window_name);
}

void display_image(cv::Mat image, const char *window_name)
{
	if (image.empty())
	{
		printf("Could not open or find the image\n");
		return;
	}
	printf("| Image size: %d x %d\n", image.cols, image.rows);
	cv::namedWindow("Display window", cv::WINDOW_GUI_NORMAL);
	printf("| %s image created\n", window_name);
	printf("----------------------------\n");
	cv::imshow("Display window", image);
	cv::waitKey(0);
}

cv::Mat profile_of_row(cv::Mat &image, int row)
{
	if (image.empty())
	{
		printf("Could not open or find the image\n");
		return cv::Mat();
	}
	if (row < 0 || row >= image.rows)
	{
		printf("Row out of bounds\n");
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

	return profile_of_row(image, row);
}

size_t *intensity_freq(cv::Mat &image)
{
	if (image.empty())
	{
		printf("Could not open or find the image\n");
		return NULL;
	}
	if (image.channels() > 1)
	{
		printf("Cannot calculate histogram to multi-channel image\n");
		return NULL;
	}

	size_t *freq = (size_t *)malloc(256 * sizeof(size_t));
	int intensity_count[256];
	for (size_t i = 0; i < 256; i++)
	{
		intensity_count[i] = 0;
	}
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			intensity_count[image.at<uchar>(i, j)] += 1;
		}
	}
	for (size_t i = 0; i < 256; i++)
	{
		freq[i] = (size_t)(((float)intensity_count[i] / (image.rows * image.cols)) * 255);
	}
	return freq;
}

size_t *intensity_freq(const char *image_path)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	return intensity_freq(image);
}

cv::Mat set_channel_to_zero(const cv::Mat &image, int channel)
{
	const int c = image.channels();
	if (channel >= c)
	{
		printf("[ERROR]: channel provided exceeds the number of channels in image\n");
		return cv::Mat();
	}

	cv::Mat modified = image.clone();
	for (size_t i = 0; i < modified.rows; i++)
	{
		for (size_t j = 0; j < modified.cols; j++)
		{
			if (c == 1)
			{
				modified.at<uchar>(i, j) = 0;
			}
			else if (c == 2)
			{
				modified.at<cv::Vec<uchar, 2>>(i, j)[channel] = 0;
			}
			else if (c == 3)
			{
				modified.at<cv::Vec<uchar, 3>>(i, j)[channel] = 0;
			}
			else
			{
				modified.at<cv::Vec<uchar, 4>>(i, j)[channel] = 0;
			}
		}
	}
	return modified;
}

std::vector<cv::Mat> split_channels(const cv::Mat &image)
{
	std::vector<cv::Mat> splitted_image(image.channels());
	cv::split(image, splitted_image);

	return splitted_image;
}

cv::Mat v_gradient()
{
	cv::Mat image = cv::Mat(cv::Size2i(256, 256), CV_8U);
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			image.at<uchar>(i, j) = i;
		}
	}

	return image;
}

cv::Mat h_gradient()
{
	cv::Mat image = cv::Mat(cv::Size2i(256, 256), CV_8U);
	for (size_t j = 0; j < image.cols; j++)
	{
		for (size_t i = 0; i < image.rows; i++)
		{
			image.at<uchar>(i, j) = j;
		}
	}

	return image;
}

cv::Mat chessboard(int width, int height, int square_size)
{
	if (width % square_size != 0 || height % square_size != 0)
	{
		printf("[ERROR]: invalid params for chessboard\n");
		return cv::Mat();
	}
	cv::Mat image = cv::Mat(cv::Size2i(width, height), CV_8U);
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			int row_index = i / square_size;
			int col_index = j / square_size;

			if ((row_index + col_index) % 2 == 0)
				image.at<uchar>(i, j) = 0;
			else
				image.at<uchar>(i, j) = 255;
		}
	}
	return image;
}

cv::Mat image_histogram(cv::Mat &image)
{
	if (image.empty())
	{
		printf("Could not open or find the image\n");
		return cv::Mat();
	}
	if (image.channels() > 1)
	{
		printf("Cannot calculate histogram to multi-channel image\n");
		return cv::Mat();
	}

	size_t *freq = intensity_freq(image);

	cv::Mat histogram = cv::Mat::zeros(cv::Size2i(256, 256), image.type());
	for (size_t j = 0; j < histogram.cols; j++)
	{
		size_t inv_perc = 255 - freq[j];
		for (size_t i = 0; i < histogram.rows; i++)
		{
			if (i < inv_perc)
				continue;
			histogram.at<uchar>(i, j) = 255;
		}
	}
	free(freq);
	return histogram;
}

cv::Mat image_histogram(const char *image_path)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
	return image_histogram(image);
}

cv::Mat apply_transformation(cv::Mat &image, uchar (*transformation)(const uchar &pixel, ParamSet param), ParamSet param)
{
	if (image.empty())
	{
		printf("Could not open or find the image\n");
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
			uchar pixel_intensity = image.at<uchar>(i, j);
			if (pixel_intensity < param.basex)
			{
				transformed_image.at<uchar>(i, j) = linear_transform(image.at<uchar>(i, j), PARAM(0, 0, param.basex, param.basey, param.param));
			}
			else if (pixel_intensity < param.targetx)
			{
				transformed_image.at<uchar>(i, j) = transformation(image.at<uchar>(i, j), param);
			}
			else
			{
				transformed_image.at<uchar>(i, j) = linear_transform(image.at<uchar>(i, j), PARAM(param.targetx, param.targety, 255, 255, param.param));
			}
		}
	}
	return transformed_image;
}

cv::Mat apply_transformation(const char *image_path, uchar (*transformation)(const uchar &pixel, ParamSet param), ParamSet param)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

	return apply_transformation(image, transformation, param);
}

cv::Mat images_diff(const char *image_path1, const char *image_path2)
{
	cv::Mat image1 = cv::imread(image_path1, cv::IMREAD_GRAYSCALE);
	cv::Mat image2 = cv::imread(image_path2, cv::IMREAD_GRAYSCALE);

	return images_diff(image1, image2);
}

cv::Mat images_diff(cv::Mat &image1, cv::Mat &image2)
{
	if (image1.empty() || image2.empty())
	{
		printf("Could not open or find images\n");
		return cv::Mat();
	}
	if (image1.size != image2.size)
	{
		printf("Image size are different. Cannot produce the difference\n");
		return cv::Mat();
	}
	if (image1.channels() > 1 || image2.channels() > 1)
	{
		printf("Cannot calculate diff of multi-channel images\n");
		return cv::Mat();
	}
	cv::Mat diff_image = cv::Mat::zeros(image1.size(), image1.type());

	for (size_t i = 0; i < image1.rows; i++)
	{
		for (size_t j = 0; j < image1.cols; j++)
		{
			diff_image.at<uchar>(i, j) = abs(image1.at<uchar>(i, j) - image2.at<uchar>(i, j));
		}
	}

	return diff_image;
}

cv::Mat gaussian_noise(const cv::Mat &src, float mean, float std)
{
	cv::Mat g = src.clone();
	cv::Mat noise = cv::Mat(g.size(), g.type());
	cv::randn(noise, mean, std);

	return g + noise;
}

cv::Mat salt_noise(const cv::Mat &src, float prob)
{
	cv::Mat s = src.clone();
	for (size_t i = 0; i < s.rows; i++)
	{
		for (size_t j = 0; j < s.cols; j++)
		{
			float p = (float)rand() / RAND_MAX;
			if (p < prob)
				s.at<uchar>(i, j) = 255;
		}
	}
	return s;
}

cv::Mat pepper_noise(const cv::Mat &src, float prob)
{
	cv::Mat s = src.clone();
	for (size_t i = 0; i < s.rows; i++)
	{
		for (size_t j = 0; j < s.cols; j++)
		{
			float p = (float)rand() / RAND_MAX;
			if (p < prob)
				s.at<uchar>(i, j) = 0;
		}
	}
	return s;
}

cv::Mat salt_pepper_noise(const cv::Mat &src, float prob)
{
	cv::Mat s = src.clone();
	for (size_t i = 0; i < s.rows; i++)
	{
		for (size_t j = 0; j < s.cols; j++)
		{
			float p = (float)rand() / RAND_MAX;
			if (p < prob)
			{
				p = (float)rand() / RAND_MAX;
				if (p < 0.5)
					s.at<uchar>(i, j) = 0;
				else
					s.at<uchar>(i, j) = 255;
			}
		}
	}
	return s;
}

void apply_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel, void (*filter_type)(cv::Mat &src, cv::Mat &dst, cv::Mat kernel))
{
	if (kernel.type() != CV_32F)
	{
		printf("Unknown type of kernel\n");
		return;
	}

	filter_type(src, dst, kernel);
}

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
