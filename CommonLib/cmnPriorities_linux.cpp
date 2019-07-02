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
   mStrobe            = Ris::Threads::Priority(-1, 95);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
