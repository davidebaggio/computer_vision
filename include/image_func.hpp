#ifndef IMAGE_FUNC_HPP
#define IMAGE_FUNC_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void display_image(const char *image_path);
void display_image(cv::Mat image);

size_t get_num_channels(const char *image_path);

void profile_of_row(const char *image_path, int row);
void profile_of_row(cv::Mat &image, int row);

cv::Mat apply_transformation(const char *image_path, uchar (*transformation)(const uchar &pixel));
cv::Mat apply_transformation(cv::Mat image, uchar (*transformation)(const uchar &pixel));

// dft of image
cv::Mat dft_calc(const char *image_path);
cv::Mat dft_calc(cv::Mat image);

#endif // IMAGE_FUNC_HPP