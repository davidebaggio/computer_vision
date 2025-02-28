#ifndef IMAGE_FUNC_HPP
#define IMAGE_FUNC_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void display_image(const char *image_path);
void display_image(cv::Mat image);

// dft of image
cv::Mat dft_calc(const char *image_path);
cv::Mat dft_calc(cv::Mat image);

#endif // IMAGE_FUNC_HPP