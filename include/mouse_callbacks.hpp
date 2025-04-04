#ifndef MOUSE_CALLBACKS_HPP
#define MOUSE_CALLBACKS_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

void means(const cv::Mat &img, int *means, int x, int y, int size);

void on_click(int event, int x, int y, int flags, void *userdata);
void on_click_mean(int event, int x, int y, int flags, void *userdata);
void on_click_mean_mask(int event, int x, int y, int flags, void *userdata);
void on_click_mean_mask_on_original(int event, int x, int y, int flags, void *userdata);

#endif // MOUSE_CALLBACKS_HPP
