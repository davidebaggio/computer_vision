#ifndef TRACKBAR_CALLBACKS_HPP
#define TRACKBAR_CALLBACKS_HPP

#include <opencv2/opencv.hpp>

typedef struct TB_args
{
	int low_th;
	int high_th;
	int max_th;
	cv::Mat img;
	cv::Mat *edges;
	char *winname;
} TB_args;

void on_slide_canny(int, void *);

#endif // TRACKBAR_CALLBACKS_HPP