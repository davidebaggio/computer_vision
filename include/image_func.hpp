#ifndef IMAGE_FUNC_HPP
#define IMAGE_FUNC_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

#include "pixel_transform.hpp"

#define KERNEL3x3(mat) cv::Mat(3, 3, CV_32F, (mat))
#define DEFKERNEL KERNEL3x3(cv::Scalar::all(0))

static float laplacian_terms[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
static float laplacian_ext_terms[] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
static float laplacian_inv_terms[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
static float laplacian_ext_inv_terms[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
static float sobelx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
static float sobely[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

void display_image(const char *image_path, const char *window_name);
void display_image(cv::Mat image, const char *window_name);

cv::Mat profile_of_row(const char *image_path, int row);
cv::Mat profile_of_row(cv::Mat &image, int row);

size_t *intensity_freq(const char *image_path);
size_t *intensity_freq(cv::Mat &image);

cv::Mat set_channel_to_zero(const cv::Mat &image, int channel);
std::vector<cv::Mat> split_channels(const cv::Mat &image);

cv::Mat v_gradient();
cv::Mat h_gradient();
cv::Mat chessboard(int width, int height, int square_size);

cv::Mat image_histogram(const char *image_path);
cv::Mat image_histogram(cv::Mat &image);

cv::Mat apply_transformation(const char *image_path, uchar (*transformation)(const uchar &pixel, ParamSet param), ParamSet param);
cv::Mat apply_transformation(cv::Mat &image, uchar (*transformation)(const uchar &pixel, ParamSet param), ParamSet param);

cv::Mat images_diff(const char *image_path1, const char *image_path2);
cv::Mat images_diff(cv::Mat &image1, cv::Mat &image2);

cv::Mat gaussian_noise(const cv::Mat &src, float mean, float std);
cv::Mat salt_noise(const cv::Mat &src, float prob);
cv::Mat pepper_noise(const cv::Mat &src, float prob);
cv::Mat salt_pepper_noise(const cv::Mat &src, float prob);

void apply_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel, void (*filter_type)(cv::Mat &src, cv::Mat &dst, cv::Mat kernel));

// linear filters
void agv_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void linear_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void sobel_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);

// non-linear filters
void mean_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void min_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void max_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void median_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);

#endif // IMAGE_FUNC_HPP