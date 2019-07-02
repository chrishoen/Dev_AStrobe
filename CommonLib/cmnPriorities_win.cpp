/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <windows.h>

#define  _CMNPRIORITIES_CPP_
#include "cmnPriorities.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Priorities::Priorities()
{
   mTsPrint           = Ris::Threads::Priority(-1, THREAD_PRIORITY_ABOVE_NORMAL);
   mLogFile           = Ris::Threads::Priority(-1, THREAD_PRIORITY_LOWEST);
   mBinaryComm        = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mSerialMsg         = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mGCodeComm         = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mSerialString      = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mGraphics          = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mScriptSeqLong     = Ris::Threads::Priority(-1, THREAD_PRIORITY_HIGHEST);
   mScriptSeqShort    = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);

   mControl           = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mControlUdp        = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);
   mIsoch             = Ris::Threads::Priority(-1, THREAD_PRIORITY_NORMAL);

   mForceSerialRx     = Ris::Threads::Priority(-1, THREAD_PRIORITY_ABOVE_NORMAL);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
