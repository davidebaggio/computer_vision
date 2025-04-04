#include "image_func.hpp"
#include "mouse_callbacks.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./task3.3 <image_path>\n");
		return 1;
	}

	const char *image_path = argv[1];
	interact_display(image_path, "Robocup", on_click_mean_mask);
}