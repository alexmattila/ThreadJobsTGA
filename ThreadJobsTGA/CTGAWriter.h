#pragma once
#include <string>

// targa file header

typedef struct
{
	char id_length;      // length of id field (number of bytes - max 255)
	char map_type;       // colormap field (0 or 1; no map or 256 entry palette)
	char image_type;     // ( 0 - no image data included
				 //	  1 - uncompressed, color mapped image
				 //	  2 - uncompressed, RGB image
				 //	  3 - uncompressed, black & white image
				 //	  9 - run-length encoded(RLE-lossless compression),color mapped image
				 //	 10 - RLE, RGB image
				 //	 11 - compressed, black & white image )

	int map_first;       // first entry index for color map
	int map_length;      // total number of entries in color map
	char map_entry_size; // number of bits per entry

	int x;               // x cooridinate of origin
	int y;               // y cooridinate of origin

	int width;           // width in pixels
	int height;          // height in pixels

	char bits_per_pixel; // number of bits per pixel

	char misc;           // srsly? "scan origin and alpha bits" this example uses scan origin
				 // honestly, don't know what's going on here. we pass in a hex value
				 // :shrug_emoji:		
} targa_header;

class CTGAWriter
{
private:
	int little_endianify(int number);
	int big_endianify(int number);

	void writeHeader(targa_header header, FILE *tga);
public:
	CTGAWriter();
	~CTGAWriter();

	bool write(std::string fileName, unsigned char* pBuffer, unsigned int width, unsigned int height);
};

