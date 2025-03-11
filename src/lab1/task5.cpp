#include "image_func.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	display_image(v_gradient(), "Vertical gradient");
	display_image(h_gradient(), "Horizontal gradient");
	display_image(chessboard(300, 300, 20), "Chessboard 20");
	display_image(chessboard(300, 300, 50), "Chessboard 50");
}