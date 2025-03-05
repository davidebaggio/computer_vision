#ifndef IMAGE_FUNC_HPP
#define IMAGE_FUNC_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "pixel_transform.hpp"

void display_image(const char *image_path, const char *window_name);
void display_image(cv::Mat image, const char *window_name);

cv::Mat profile_of_row(const char *image_path, int row);
cv::Mat profile_of_row(cv::Mat &image, int row);

cv::Mat apply_transformation(const char *image_path, uchar (*transformation)(const uchar &pixel, ParamSet param), ParamSet param);
cv::Mat apply_transformation(cv::Mat &image, uchar (*transformation)(const uchar &pixel, ParamSet param), ParamSet param);

cv::Mat images_diff(const char *image_path1, const char *image_path2);
cv::Mat images_diff(cv::Mat &image1, cv::Mat &image2);

// dft of image
cv::Mat dft_calc(const char *image_path);
cv::Mat dft_calc(cv::Mat image);

#endif // IMAGE_FUNC_HPP