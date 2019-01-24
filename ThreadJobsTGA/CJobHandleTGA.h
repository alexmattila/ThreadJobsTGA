#pragma once
#include "IJob.h"
#include <string>

class CJobHandleTGA : public IJob
{
private:
	unsigned char* m_pMainPixelBuffer;
	unsigned char* m_pThisPixelBuffer;

	unsigned int m_indexStartPosition;
	unsigned int m_index;
	unsigned int m_chunkSize;
	unsigned int m_numPixelsToCreate;
	unsigned int m_outputWidth;
	unsigned int m_outputHeight;
public:
	CJobHandleTGA(unsigned int index, unsigned int indexPosition, unsigned int chunkSize, unsigned int outputWidth, unsigned int outputHeight, unsigned char* pPixelBuffer);
	~CJobHandleTGA();

	bool executeJob() override;
	void onJobFinished() override;
};

