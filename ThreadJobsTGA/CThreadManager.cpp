#include "CThreadManager.h"
#include "CJobManager.h"



CThreadManager::CThreadManager()
{
}


CThreadManager::~CThreadManager()
{
	size_t numThreads = m_threads.size();
	for (size_t i = 0; i < numThreads; i++)
	{
		m_threads[i]->join();

		delete m_threads[i];
	}
}

std::thread* CThreadManager::startThread(CJobManager* pJobManager)
{
	lock();
	std::thread* pThread = new std::thread(&CJobManager::doJobs, pJobManager);
	m_threads.push_back(pThread);
	unlock();

	return pThread;
}

void CThreadManager::lock()
{
	m_mutex.lock();
}

void CThreadManager::unlock()
{
	m_mutex.unlock();
}
