#include <stdio.h>
#include "CTGAWriter.h"

#include <iostream>

#define BYTE_RANGE 256;
#define NUM_COLOR_CHANNELS 4

CTGAWriter::CTGAWriter()
{
}

CTGAWriter::~CTGAWriter()
{
}

bool CTGAWriter::write(std::string fileName, unsigned char* pBuffer, unsigned int width, unsigned int height)
{
	FILE *tga; // pointer to file that we will write
	targa_header header; // variable of targa_header type

	// set header values

	header.id_length = 0;
	header.map_type = 0;
	header.image_type = 2; // uncompressed RGB image

	header.map_first = 0;
	header.map_length = 0;
	header.map_entry_size = 0;

	header.x = 0;
	header.y = 0;
	header.width = width;
	header.height = height;

	header.bits_per_pixel = 8 * NUM_COLOR_CHANNELS;
	header.misc = 0x20; // scan from upper left corner

	// start to write file
	fopen_s(&tga, fileName.c_str(), "wb");
	if (!tga)
	{
		std::cout << "Error writing tga file\n";
		return false;
	}

	writeHeader(header, tga);

	// magic happens here -- write the pixels

	unsigned int index = 0;
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			//unsigned int index = (y * width) + (x * NUM_COLOR_CHANNELS);

			// ARGB backwards for some reason
			fputc(pBuffer[index + 2], tga);
			fputc(pBuffer[index + 1], tga);
			fputc(pBuffer[index + 0], tga);
			fputc(pBuffer[index + 3], tga);

			index += NUM_COLOR_CHANNELS;
		}

	std::cout << "Saved " << index / 4 << " pixels\n";

	// magic ends here

	fclose(tga);

	return true;
}

int CTGAWriter::little_endianify(int number)
{
	return number % BYTE_RANGE;
}

int CTGAWriter::big_endianify(int number)
{
	return number / BYTE_RANGE;
}

void CTGAWriter::writeHeader(targa_header header, FILE *tga)
{
	fputc(header.id_length, tga);
	fputc(header.map_type, tga);
	fputc(header.image_type, tga);

	fputc(little_endianify(header.map_first), tga);
	fputc(big_endianify(header.map_first), tga);

	fputc(little_endianify(header.map_length), tga);
	fputc(big_endianify(header.map_length), tga);

	fputc(header.map_entry_size, tga);

	fputc(little_endianify(header.x), tga);
	fputc(big_endianify(header.x), tga);
	fputc(little_endianify(header.y), tga);
	fputc(big_endianify(header.y), tga);

	fputc(little_endianify(header.width), tga);
	fputc(big_endianify(header.width), tga);
	fputc(little_endianify(header.height), tga);
	fputc(big_endianify(header.height), tga);

	fputc(header.bits_per_pixel, tga);
	fputc(header.misc, tga);
}

//#include "CTGAWriter.h"
//
//#include <iostream>
//#include <fstream>
//
//CTGAWriter::CTGAWriter()
//{
//}
//
//
//CTGAWriter::~CTGAWriter()
//{
//}
//
//bool CTGAWriter::write(std::string fileName, unsigned char* pBuffer, unsigned int width, unsigned int height)
//{
//	std::cout << "Saving to " << fileName << std::endl;
//
//	std::ofstream tgafile(fileName.c_str(), std::ios::binary);
//	if (!tgafile)
//	{
//		std::cout << "Error loading file " << fileName << std::endl;
//		return false;
//	}
//
//	// The image header
//	unsigned char header[18] = { 0 };
//	header[2] = 2;
//	header[12] = width & 0xFF;
//	header[13] = (width >> 8) & 0xFF;
//	header[14] = height & 0xFF;
//	header[15] = (height >> 8) & 0xFF;
//	header[16] = 32;  // bits per pixel
//
//	tgafile.write((const char*)header, 18);
//
//	// The image data is stored bottom-to-top, left-to-right
//	int numPixels = (width * height) / 4;
//	for (int i = 0; i < numPixels; i++)
//	{
//		unsigned int index = i * 4;
//
//		tgafile.put(pBuffer[index]);
//		tgafile.put(pBuffer[index + 1]);
//		tgafile.put(pBuffer[index + 2]);
//		tgafile.put(pBuffer[index + 3]);
//	}
//
//	// The file footer. This part is totally optional.
//	static const char footer[26] =
//		"\0\0\0\0"  // no extension area
//		"\0\0\0\0"  // no developer directory
//		"TRUEVISION-XFILE"  // yep, this is a TGA file
//		".";
//	tgafile.write(footer, 26);
//
//	tgafile.close();
//
//	return true;
//}