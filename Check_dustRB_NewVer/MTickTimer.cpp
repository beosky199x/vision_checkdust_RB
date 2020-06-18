#include "MTickTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MTickTimer::MTickTimer()
{
	m_bIsStart = FALSE;

    //StartTimer();
}

MTickTimer::~MTickTimer()
{
}


int MTickTimer::StartTimer()
{

    m_dwStart = timer.elapsed();
	m_bIsStart = TRUE;
	return DEF_TIMER_SUCCESS;
}


int MTickTimer::StopTimer()
{
	if(!m_bIsStart) return ERR_TIMER_NOT_STARTED;
	m_bIsStart = FALSE;
	return DEF_TIMER_SUCCESS;
}


double	MTickTimer::GetElaspTime()
{
    qint64	dwStop;
    qint64	dwElasp;


    dwStop      = timer.elapsed();
	if(!m_bIsStart)	return 0.;

	if (m_dwStart <= dwStop)			//check for wrap around condition
	{
		dwElasp = dwStop - m_dwStart;	//no wrap
	}
	else
	{
		dwElasp = (0xFFFFFFFFL - m_dwStart); //calculate time from start up to wrap
		dwElasp += 1;   //time to wrap from FFFFFFFF to 0 is 1 tick
		dwElasp += dwStop; //add in time after  0
	}

	return (double)dwElasp/1000.;
}


bool MTickTimer::LessThan(double dSec)
{
	if( GetElaspTime() < dSec ) return TRUE;
	else return FALSE;
}


bool MTickTimer::MoreThan(double dSec)
{
	if( GetElaspTime() > dSec ) return TRUE;
	else return FALSE;
}


bool MTickTimer::IsTimerStarted() const
{
	return m_bIsStart;
}

/* End Of Code */
