/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
   mTsPrint           = Ris::Threads::Priority(-1, 20);
   mLogFile           = Ris::Threads::Priority(-1, 21);
   mBinaryComm        = Ris::Threads::Priority( 3, 51);
   mBinarySim         = Ris::Threads::Priority(-1, 35);
   mSerialMsg         = Ris::Threads::Priority( 3, 80);
   mGCodeComm         = Ris::Threads::Priority(-1, 60);
   mSerialString      = Ris::Threads::Priority(-1, 80);
   mGraphics          = Ris::Threads::Priority(-1, 40);
   mScriptSeqLong     = Ris::Threads::Priority(-1, 50);
   mScriptSeqShort    = Ris::Threads::Priority(-1, 70);

   mControl           = Ris::Threads::Priority(-1, 40);
   mControlUdp        = Ris::Threads::Priority(-1, 60);
   mIsoch             = Ris::Threads::Priority(-1, 40);

   mForceSerialRx     = Ris::Threads::Priority(-1, 80);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
