#include "IJob.h"

IJob::IJob() :
	m_isFinished(false),
	m_isReserved(false)
{
}

IJob::~IJob()
{
}

void IJob::setFinished(bool finished)
{
	if (m_isFinished != finished)
	{
		onJobFinished();
		m_isFinished = finished;
	}
}
