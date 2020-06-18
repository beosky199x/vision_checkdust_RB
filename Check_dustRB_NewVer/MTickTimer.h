#ifndef MTICKTIMER_H
#define MTICKTIMER_H
#include <QElapsedTimer>
const int DEF_TIMER_SUCCESS		= 0;		
const int ERR_TIMER_NOT_STARTED	= 1;
const int ERR_TIMER_ALREADY_STARTED = 2;

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

class MTickTimer   {
public:
	MTickTimer();
	virtual ~MTickTimer();
private:
    bool m_bIsStart;
    qint64 m_dwStart;
    QElapsedTimer timer;

public:
	int	StartTimer();
    int	StopTimer();
    double GetElaspTime();
    bool LessThan(double dSec);
    bool MoreThan(double dSec);
    bool IsTimerStarted() const;
};

#endif // MTICKTIMER_H
