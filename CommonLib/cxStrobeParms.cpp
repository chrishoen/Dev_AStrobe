//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"
#include "cisCProcDir.h"

#define  _CXSTROBEPARMS_CPP_
#include "cxStrobeParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CX
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
   BaseClass::setFilePath("./files/Strobe_Parms.txt");

   mTimerThreadPeriod = 0;
   mShowCode = 0;
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
   printf("ShowCode                   %-10d\n", mShowCode);
   printf("TimerThreadPeriod          %-10d\n", mTimerThreadPeriod);

   printf("\n");
   printf("StrobePrintLevel           %-10s\n", mStrobePrintLevel.asString(tBuffer));
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

   if (aCmd->isCmd("ShowCode"))                 mShowCode = aCmd->argInt(1);
   if (aCmd->isCmd("TimerThreadPeriod"))        mTimerThreadPeriod = aCmd->argInt(1);

   if (aCmd->isCmd("StrobePrintLevel"))         mStrobePrintLevel.readArgs(aCmd);
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