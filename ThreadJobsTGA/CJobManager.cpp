#include "CJobManager.h"
#include "CJobHandleTGA.h"

#include <iostream>
#include <Windows.h>

#define TGACONVERT_NUM_THREADS 4

CJobManager::CJobManager() :
	m_jobsActive(true)
{
	
}


CJobManager::~CJobManager()
{
	size_t numJobs = m_jobs.size();
	if (numJobs > 0)
	{
		std::cout << numJobs << " jobs left on shutdown. you were supposed to finish them\n";

		for (size_t i = 0; i < numJobs; i++)
		{
			delete m_jobs[i];
		}
	}
}

void CJobManager::startThreads(short int numThreads)
{
	for (int i = 0; i < numThreads; i++)
	{
		m_threadManager.startThread(this);
	}
}

IJob* CJobManager::getNextJob()
{
	m_threadManager.lock();
	for (size_t i = 0; i < m_jobs.size(); i++)
	{
		if (m_jobs[i]->isFinished()) // Job is done - remove it
		{
			delete m_jobs[i];
			std::swap(m_jobs[i], m_jobs.back());
			m_jobs.pop_back();

			continue;
		}

		if (!m_jobs[i]->isReserved())
		{
			m_jobs[i]->setReserved(true);

			std::cout << "Found job, reserving it.\n";
			m_threadManager.unlock();

			return m_jobs[i];
		}
	}
	m_threadManager.unlock();

	//std::cout << "No job found!\n";

	return nullptr;
}

void CJobManager::insertJob(IJob* pJob)
{
	m_threadManager.lock();
	m_jobs.push_back(pJob);
	m_threadManager.unlock();
}

void CJobManager::exit()
{
	m_jobsActive = false;
	std::cout << "Exititing Job manager\n";
}

void CJobManager::doTgaConvertJob(int width, int height, unsigned char* pPixelBuffer)
{
	// Create jobs
	const int chunkSize = 16 * 16;
	for (int i = 0; i < width; i++)
	{
		insertJob(new CJobHandleTGA(i, i * chunkSize * 4, chunkSize, width, height, pPixelBuffer));
	}

	// Start threads
	startThreads(TGACONVERT_NUM_THREADS);
}

void CJobManager::doJobs()
{
	// Do the jobs
	while (m_jobsActive)
	{
		IJob* pJob = getNextJob();
		if (pJob != nullptr)
		{
			std::cout << "Executing job..\n";

			pJob->executeJob();
		}
		else
		{
			Sleep(1);
		}
	}
}
