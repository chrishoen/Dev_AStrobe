#pragma once

/*==============================================================================
Timer test thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreadsTimerThread.h"
#include "risTimeMarker.h"

#include "GPIO.h"

using namespace exploringBB;

namespace AX
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class StrobeThread : public Ris::Threads::BaseTimerThread
{
public:
   typedef Ris::Threads::BaseTimerThread BaseClass;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Members.

   Ris::PeriodicTimeMarker mTimeMarker;

   bool mTPFlag;
   int  mTestCode;
   int  mTestCount;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Members.

   GPIO mOutGPIO;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   StrobeThread();

   // Base class overloads.
   void threadInitFunction() override;
   void threadExitFunction() override;
   void executeOnTimer(int aTimeCount) override;

   void executeTest1 (int aTimeCount);
   void executeTest2 (int aTimeCount);
   void executeTest3 (int aTimeCount);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _AXSTROBETHREAD_CPP_
          StrobeThread* gStrobeThread;
#else
   extern StrobeThread* gStrobeThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


