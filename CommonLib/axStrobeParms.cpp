//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _AXSTROBEPARMS_CPP_
#include "axStrobeParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace AX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StrobeParms::StrobeParms()
{
   reset();
}

void StrobeParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath_RelativeToBaseDir("files/Strobe_Parms.txt");

   mStrobeEnable = false;
   mPruRxEnable = false;
   mShowCode = 0;

   mTestCode = 0;
   mTimerThreadPeriod = 0;
   mTimeMarkerSize = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StrobeParms::show()
{
   char tBuffer[40];
   printf("\n");
   printf("StrobeParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("StrobeEnable                %-10s\n", my_string_from_bool(mStrobeEnable));
   printf("PruRxEnable                 %-10s\n", my_string_from_bool(mPruRxEnable));
   printf("\n");
   printf("StrobePrintLevel            %-10s\n", mStrobePrintLevel.asString(tBuffer));
   printf("PruRxPrintLevel             %-10s\n", mPruRxPrintLevel.asString(tBuffer));
   printf("\n");
   printf("ShowCode                    %-10d\n", mShowCode);
   printf("TestCode                    %-10d\n", mTestCode);
   printf("TimerThreadPeriod           %-10d\n", mTimerThreadPeriod);
   printf("TimeMarkerSize              %-10d\n", mTimeMarkerSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StrobeParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("StrobeEnable"))             mStrobeEnable = aCmd->argBool(1);
   if (aCmd->isCmd("PruRxEnable"))              mPruRxEnable = aCmd->argBool(1);
   if (aCmd->isCmd("StrobePrintLevel"))         mStrobePrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("PruRxPrintLevel"))          mPruRxPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("ShowCode"))                 mShowCode = aCmd->argInt(1);

   if (aCmd->isCmd("TestCode"))                 mTestCode = aCmd->argInt(1);
   if (aCmd->isCmd("TimerThreadPeriod"))        mTimerThreadPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("TimeMarkerSize"))           mTimeMarkerSize = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StrobeParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace