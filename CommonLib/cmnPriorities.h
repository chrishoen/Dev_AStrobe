#pragma once

/*==============================================================================
This file provides a set of variables that are used to define thread
priorities and processor number for threads in these programs.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsPriorities.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a set of variables that are used to define thread
// priorities and thread single processor numbers for threads in these
// programs.

class Priorities
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   Ris::Threads::Priority mTsPrint;
   Ris::Threads::Priority mLogFile;
   Ris::Threads::Priority mBinaryComm;
   Ris::Threads::Priority mBinarySim;
   Ris::Threads::Priority mSerialMsg;
   Ris::Threads::Priority mGCodeComm;
   Ris::Threads::Priority mSerialString;
   Ris::Threads::Priority mGraphics;
   Ris::Threads::Priority mScriptSeqLong;
   Ris::Threads::Priority mScriptSeqShort;
   Ris::Threads::Priority mControl;
   Ris::Threads::Priority mControlUdp;
   Ris::Threads::Priority mIsoch;
   Ris::Threads::Priority mForceSerialRx;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   Priorities();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _CMNPRIORITIES_CPP_
          Priorities gPriorities;
#else
   extern Priorities gPriorities;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

