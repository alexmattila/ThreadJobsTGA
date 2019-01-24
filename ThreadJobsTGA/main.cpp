#include "CJobManager.h"
#include "tga_reader.h"
#include <iostream>
#include <Windows.h>

int main()
{
	// Read the file
	int width = 0;
	int height = 0;
	int* pPixels = nullptr;

	const char* fileName = "images/psq_logga_original.tga";

	FILE* file = nullptr;
	fopen_s(&file, fileName, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);

		unsigned char *buffer = (unsigned char *)tgaMalloc(size);
		fread(buffer, 1, size, file);
		fclose(file);

		pPixels = tgaRead(buffer, TGA_READER_ABGR);
		width = tgaGetWidth(buffer);
		height = tgaGetHeight(buffer);

		tgaFree(buffer);
	}
	else
	{
		std::cout << "Error reading file " << fileName << std::endl;
		return false;
	}

	unsigned char* pPixelBuffer = (unsigned char*)pPixels;

	CJobManager jobManager;
	jobManager.doTgaConvertJob(width, height, pPixelBuffer);
	while (jobManager.getNumJobs() > 0)
	{
		Sleep(1);
	}
	jobManager.exit();

	return 0;
}
