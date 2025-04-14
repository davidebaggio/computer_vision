#include "image_func.hpp"

void display_image(cv::Mat image, const char *window_name)
{
	if (image.empty())
	{
		printf("[ERROR]: Could not open or find the image\n");
		return;
	}
	printf("| Image size: %d x %d\n", image.cols, image.rows);
	cv::namedWindow("Display window", cv::WINDOW_GUI_NORMAL);
	printf("| %s image created\n", window_name);
	printf("----------------------------\n");
	cv::imshow("Display window", image);
	cv::waitKey(0);
}

void display_image(const char *image_path, const char *window_name)
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
	display_image(image, window_name);
}

void interact_display(cv::Mat image, const char *window_name, void (*mouse_callback)(int event, int x, int y, int flags, void *userdata))
{
	if (image.empty())
	{
		printf("[ERROR]: Could not open or find the image\n");
		return;
	}

	printf("| Image size: %d x %d\n", image.cols, image.rows);
	cv::namedWindow("Display window", cv::WINDOW_GUI_NORMAL);
	cv::setMouseCallback("Display window", mouse_callback, &image);
	printf("| %s image created\n", window_name);
	printf("----------------------------\n");
	cv::imshow("Display window", image);
	cv::waitKey(0);
}

void interact_display(const char *image_path, const char *window_name, void (*mouse_callback)(int event, int x, int y, int flags, void *userdata))
{
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
	interact_display(image, window_name, mouse_callback);
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

void interact_trackbars(void (*on_change)(int, void *), TB_args userdata)
{
	if (userdata.img.empty())
	{
		printf("[ERROR]: Could not open image\n");
	}

	cv::createTrackbar("Low TRESHOLD", userdata.winname, &(userdata.low_th), userdata.max_th, on_change, (void *)&userdata);
	cv::createTrackbar("High TRESHOLD", userdata.winname, &(userdata.high_th), userdata.max_th, on_change, (void *)&userdata);

	on_change(0, (void *)&userdata);
	cv::waitKey(0);
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

// TODO: add support for multi channel images
cv::Mat calculate_histogram(const cv::Mat &image, int bins, const float *hist_range[])
{
	if (image.empty())
	{
		printf("[ERROR]: cannot open image for calculating histogram\n");
		return cv::Mat();
	}
	if (image.channels() > 1)
	{
		printf("Cannot calculate histogram to multi-channel image\n");
		return cv::Mat();
	}

	bool uniform = true, accumulate = false;
	cv::Mat hist;
	cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &bins, hist_range, uniform, accumulate);

	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins);

	cv::Mat hist_image(hist_h, hist_w, CV_8U, cv::Scalar(0));
	cv::normalize(hist, hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < bins; i++)
	{
		line(hist_image, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			 cv::Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
			 cv::Scalar(255, 0, 0), 2, 8, 0);
	}

	return hist_image;
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
	if (kernel.rows % 2 != 1 || kernel.cols % 2 != 1)
	{
		printf("[ERROR]: Invalid size of kernel\n");
		return;
	}

	filter_type(src, dst, kernel);
}

// TODO: finish developement of edge_points function
std::vector<cv::Point2i> edge_points(const cv::Mat &image)
{
	if (image.empty())
	{
		printf("[ERROR]: could not open image\n");
		return std::vector<cv::Point2i>();
	}
	return std::vector<cv::Point2i>();
}

std::vector<cv::Point2i> computeIntersections(const cv::Vec2f &line, const cv::Size2i &imgSize)
{
	std::vector<cv::Point2i> points;
	float rho = line[0], theta = line[1];
	double a = cos(theta), b = sin(theta);
	double x0 = a * rho, y0 = b * rho;
	cv::Point2i pt1, pt2;

	pt1.x = cvRound(x0 + 1000 * (-b));
	pt1.y = cvRound(y0 + 1000 * (a));
	pt2.x = cvRound(x0 - 1000 * (-b));
	pt2.y = cvRound(y0 - 1000 * (a));

	// Clip line to image boundaries
	cv::LineIterator it(cv::Mat(imgSize, CV_8UC1), pt1, pt2, 8);
	for (int i = 0; i < it.count; i++, ++it)
	{
		cv::Point pt = it.pos();
		if (pt.x >= 0 && pt.x < imgSize.width && pt.y >= 0 && pt.y < imgSize.height)
		{
			points.push_back(pt);
		}
	}
	return points;
}

void poly_in_hough_lines(const cv::Mat &image, const cv::Mat &edges, cv::Mat &dest)
{
	if (image.empty())
	{
		printf("[ERROR]: Could not open image\n");
		return;
	}

	std::vector<cv::Vec4f> lines;
	cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 130, 100, 40); // best param to detect the lines on the road

	if (lines.size() < 2)
	{
		printf("[ERROR]: Less than two lines detected\n");
		return;
	}

	// sort by strongest line
	std::sort(lines.begin(), lines.end(), [](const cv::Vec4f &a, const cv::Vec4f &b)
			  { return cv::norm(a) > cv::norm(b); });

	dest = image.clone();

	std::vector<cv::Point2i> polygon = {cv::Point2i(lines[0][0], lines[0][1]),
										cv::Point2i(lines[0][2], lines[0][3]),
										cv::Point2i(lines[1][0], lines[1][1]),
										cv::Point2i(lines[1][2], lines[1][3])};

	fillConvexPoly(dest, polygon, cv::Scalar(0, 0, 255), cv::LINE_4);
}

void poly_in_hough_circles(const cv::Mat &image, const cv::Mat &edges, cv::Mat &dest)
{
	if (image.empty())
	{
		printf("[ERROR]: Could not open image\n");
		return;
	}

	std::vector<cv::Vec4f> circles;
	HoughCircles(edges, circles, cv::HOUGH_GRADIENT, 1, 20, 100, 20, 5, 40);

	if (circles.size() < 1)
	{
		printf("[ERROR]: No circle detected\n");
		return;
	}

	// sort by strongest circle
	std::sort(circles.begin(), circles.end(), [](const cv::Vec4f &a, const cv::Vec4f &b)
			  { return a[3] > b[3]; });

	dest = image.clone();
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point2i center = cv::Point2i(circles[i][0], circles[i][1]);
		int radius = circles[i][2];
		cv::circle(dest, center, radius, cv::Scalar(0, 255, 0), cv::LINE_AA);
	}
}

void segment_sky(const cv::Mat &image, cv::Mat &dest)
{
	if (image.empty())
	{
		printf("[ERROR]: Could not open image\n");
		return;
	}

	if (image.channels() < 3)
	{
		printf("[ERROR]: original BGR image is required\n");
		return;
	}

	cv::Scalar lower_sky(200, 140, 85); // Adjusted for the sky in the image
	cv::Scalar upper_sky(255, 245, 175);

	inRange(image, lower_sky, upper_sky, dest);
}

void segment_sky_with_kmeans(const cv::Mat &image, cv::Mat &dest)
{
	cv::Mat samples = image.reshape(1, image.rows * image.cols);
	samples.convertTo(samples, CV_32F);

	int K = 5;
	cv::Mat labels, centers;
	kmeans(samples, K, labels,
		   cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0),
		   3, cv::KMEANS_PP_CENTERS, centers);

	cv::Vec3f ref_color(230, 190, 130); // Adjusted for the sky in the image
	int sky_cluster = 0;
	float min_dst = FLT_MAX;

	for (int i = 0; i < K; ++i)
	{
		cv::Vec3f center = centers.at<cv::Vec3f>(i);
		float distance = cv::norm(center - ref_color); // Euclidean distance
		if (distance < min_dst)
		{
			min_dst = distance;
			sky_cluster = i;
		}
	}

	cv::Mat mask(image.size(), CV_8UC1);
	for (int y = 0; y < image.rows; ++y)
	{
		for (int x = 0; x < image.cols; ++x)
		{
			int cluster_id = labels.at<int>(y * image.cols + x);
			mask.at<uchar>(y, x) = (cluster_id == sky_cluster) ? 255 : 0;
		}
	}

	dest = mask;
}
