/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risProgramTime.h"
#include "risThreadsPriorities.h"
#include "tsThreadServices.h"

#include "cmnPriorities.h"
#include "cxStrobeParms.h"

#define  _CXSTROBETHREAD_CPP_
#include "cxStrobeThread.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

StrobeThread::StrobeThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Strobe");
   BaseClass::setThreadPrintLevel(gStrobeParms.mStrobePrintLevel);

   // Set base class variables.
   BaseClass::setThreadPriority(Cmn::gPriorities.mStrobe);

   // Set timer period.
   BaseClass::mTimerPeriod = gStrobeParms.mTimerThreadPeriod;
   mTimeMarker.initialize(gStrobeParms.mTimeMarkerSize);

   // Members
   mTPFlag = false;
   mTestCode = 1;
   mTestCount = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StrobeThread::threadInitFunction()
{
   if (mTestCode !=3) return;

   BaseClass::showThreadFullInfo();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StrobeThread::executeOnTimer(int aTimeCount)
{
   if (aTimeCount < 20) return;

   switch (mTestCode)
   {
      case 1: executeTest1 (aTimeCount); break;
      case 2: executeTest2 (aTimeCount); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StrobeThread::executeTest1(int aTimeCount)
{
   mTimeMarker.doUpdate();

   if (mTimeMarker.mStatistics.mEndOfPeriod)
   {
//    TS::print(0, "CURRENT %10.4f", Ris::getCurrentProgramTime());
      TS::print(0, "TEST1 %5d %1d %5d $$ %10.3f %10.3f %10.3f %10.3f $$ %10.3f",
         mTestCount++,
         BaseClass::getThreadProcessorNumber(),
         mTimeMarker.mStatistics.mSize,
         mTimeMarker.mStatistics.mMean,
         mTimeMarker.mStatistics.mStdDev,
         mTimeMarker.mStatistics.mMinX,
         mTimeMarker.mStatistics.mMaxX,
         mTimeMarker.mStatistics.mMaxX - mTimeMarker.mStatistics.mMinX);
      mTimeMarker.mStatistics.mEndOfPeriod = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StrobeThread::executeTest2(int aTimeCount)
{
   Prn::print(Prn::ThreadRun1, "TEST2 %5d $$ %3d %10.4f",
      aTimeCount,
      BaseClass::getThreadProcessorNumber(),
      Ris::getCurrentProgramTime());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace