#ifndef _UBER_NOISE_BMP_WRITER_H
#define _UBER_NOISE_BMP_WRITER_H

#include <cstdlib>
#include <fstream>

#pragma pack(push, 1)
// src:
// https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html
struct bm_file_header
{
	int8_t bfType[2] = {'B', 'M'};
	uint32_t bfSize = 0;
	uint16_t bfReserved1 = 0;
	uint16_t bfReserved2 = 0;
	uint32_t bfOffBits = 1078;
};

struct bm_info_header
{
	uint32_t biSize = 40;
	int32_t biWidth = 100;
	int32_t biHeight = 100;
	uint16_t biPlanes = 1;
	uint16_t biBitCount = 24;
	uint32_t biCompression = 0;
	uint32_t biSizeImage = 0;
	uint32_t biXPelsPerMeter = 0;
	uint32_t biYPelsPerMeter = 0;
	uint32_t biClrUsed = 0;
	uint32_t biClrImportant = 0;
};
#pragma pack(pop)

class bmp_img
{
private:
	uint32_t m_width;
	uint32_t m_data_width;
	uint32_t m_height;

	uint32_t m_size;
	uint8_t *m_data;

public:
	bmp_img(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;
		// width multiple as 4
		m_data_width = width * 3;
		uint32_t rem = m_data_width % 4;
		if (rem != 0)
			m_data_width = m_data_width + 4 - rem;

		m_size = m_data_width * height;

		m_data = (uint8_t *)malloc(m_size);
	}
	~bmp_img() { free(m_data); }

	void set_pixel(unsigned int x, unsigned int y, uint8_t r, uint8_t g,
		       uint8_t b)
	{
		if (x > m_width || y > m_height)
		{
			printf("pixel out of range");
			return;
		}
		m_data[(y * m_data_width) + (x * 3)] = r;
		m_data[(y * m_data_width) + (x * 3) + 1] = g;
		m_data[(y * m_data_width) + (x * 3) + 2] = b;
	}
	uint32_t width() { return m_width; }
	uint32_t height() { return m_height; }

	void write_to(const std::string &path)
	{
		// BITMAPFILEHEADER
		std::ofstream stream(path);

		bm_file_header file_header;
		bm_info_header info_header;

		uint32_t headers_size =
		    sizeof(bm_file_header) + sizeof(bm_info_header);
		file_header.bfOffBits = headers_size;
		file_header.bfSize = headers_size + m_size;

		info_header.biWidth = m_width;
		info_header.biHeight = m_height;

		stream.write((char *)&file_header, sizeof(bm_file_header));
		stream.write((char *)&info_header, sizeof(bm_info_header));

		stream.write((char *)m_data, m_size);
	}
};

#endif