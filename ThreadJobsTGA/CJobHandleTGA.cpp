#include "CJobHandleTGA.h"
#include "tga_reader.h"
#include "CTGAWriter.h"

#include <iostream>

#define NUM_COLOR_CHANNELS 4

CJobHandleTGA::CJobHandleTGA(unsigned int index, unsigned int indexPosition, unsigned int chunkSize, unsigned int outputWidth, unsigned int outputHeight, unsigned char* pPixelBuffer) :
	m_indexStartPosition(indexPosition),
	m_index(index),
	m_chunkSize(chunkSize),
	m_outputWidth(outputWidth),
	m_outputHeight(outputHeight),
	m_pMainPixelBuffer(pPixelBuffer)
{
	m_numPixelsToCreate = m_outputWidth * m_outputHeight;
	m_pThisPixelBuffer = new unsigned char[m_numPixelsToCreate * NUM_COLOR_CHANNELS];
}


CJobHandleTGA::~CJobHandleTGA()
{

}

bool CJobHandleTGA::executeJob()
{
	unsigned int mainIndexPosition = m_indexStartPosition;
	unsigned int subIndexPosition = 0;
	
	unsigned int numPixelsCreated = 0;
	for (int i = 0; i < m_chunkSize; i++) // For every pixel in the main buffer
	{
		unsigned int r = m_pMainPixelBuffer[mainIndexPosition + 0];
		unsigned int g = m_pMainPixelBuffer[mainIndexPosition + 1];
		unsigned int b = m_pMainPixelBuffer[mainIndexPosition + 2];
		unsigned int a = m_pMainPixelBuffer[mainIndexPosition + 3];

		// Create sub-pixels
		for (int j = 0; j < m_chunkSize; j++)
		{
			m_pThisPixelBuffer[subIndexPosition + 0] = r;
			m_pThisPixelBuffer[subIndexPosition + 1] = g;
			m_pThisPixelBuffer[subIndexPosition + 2] = b;
			m_pThisPixelBuffer[subIndexPosition + 3] = a;

			//std::cout << "Red " << r << ", Green " << g << ", Blue " << b << ", Alpha " << a << std::endl;
			subIndexPosition += NUM_COLOR_CHANNELS;
			numPixelsCreated++;
		}

		mainIndexPosition += NUM_COLOR_CHANNELS;
	}

	std::cout << "Created " << numPixelsCreated << " pixels\n";

	// Write to file
	CTGAWriter tgaWriter;
	tgaWriter.write("images/output/psq_output_" + std::to_string(m_index) + ".tga", m_pThisPixelBuffer, m_outputWidth, m_outputHeight);

	setFinished(true);

	return true;
}

void CJobHandleTGA::onJobFinished()
{
	std::cout << "Finished job " << this << std::endl;
}
