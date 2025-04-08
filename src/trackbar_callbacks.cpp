#include "trackbar_callbacks.hpp"

void on_slide_canny(int, void *userdata)
{
	TB_args data = *(TB_args *)userdata;
	cv::Canny(data.img, *(data.edges), data.low_th, data.high_th);
	cv::imshow(data.winname, *(data.edges));
}