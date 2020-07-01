
#include "bmp_writer.h"

int main()
{

	bmp_img img(127, 127);

	for (uint32_t x = 0; x < 127; x++)
	{
		for (uint32_t y = 0; y < 127; y++)
			img.set_pixel(x, y, x + y, x + y, x + y);
	}

	img.write_to("./img.bmp");

	return 0;
}