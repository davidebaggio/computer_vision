#ifndef IMAGE_FILTERS_HPP
#define IMAGE_FILTERS_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

// linear filters
void agv_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void linear_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void sobel_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);

// non-linear filters
void mean_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void min_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void max_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);
void median_filter(cv::Mat &src, cv::Mat &dst, cv::Mat kernel);

#endif