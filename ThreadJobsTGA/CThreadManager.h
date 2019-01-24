#pragma once
#include <thread>
#include <mutex>
#include <vector>

class CJobManager;

class CThreadManager
{
private:
	std::mutex m_mutex;

	std::vector<std::thread*> m_threads;
public:
	CThreadManager();
	~CThreadManager();

	std::thread* startThread(CJobManager* pJobManager);

	void lock();
	void unlock();
};

