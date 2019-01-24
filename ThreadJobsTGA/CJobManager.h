#pragma once
#include "CThreadManager.h"

#include <vector>

class IJob;

class CJobManager
{
private:
	CThreadManager m_threadManager;

	std::vector<IJob*> m_jobs;

	bool m_jobsActive;

	void startThreads(short int numThreads);
public:
	CJobManager();
	~CJobManager();

	size_t getNumJobs() const { return m_jobs.size(); }

	IJob* getNextJob();

	void insertJob(IJob* pJob);
	void exit();
	void doTgaConvertJob(int width, int height, unsigned char* pPixelBuffer);
	void doJobs();
};

