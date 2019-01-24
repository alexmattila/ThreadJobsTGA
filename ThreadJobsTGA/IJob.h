#pragma once

class IJob
{
private:
	bool m_isReserved;
	bool m_isFinished;
protected:
	void setFinished(bool finished);
public:
	IJob();
	virtual ~IJob();

	bool isFinished() const { return m_isFinished; }

	bool isReserved() const { return m_isReserved; }
	void setReserved(bool reserved) { m_isReserved = reserved; }

	virtual bool executeJob() = 0;
	virtual void onJobFinished() = 0;
};
