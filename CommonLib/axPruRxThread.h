#pragma once

/*==============================================================================
PRU receive thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>

#include "risThreadsThreads.h"

namespace AX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Udp string thread.
//
// This is a thread that provides the execution context for a udp peer that
// that communicates strings with another udp peer.
//

class PruRxThread : public Ris::Threads::BaseThreadWithTermFlag
{
public:
   typedef Ris::Threads::BaseThreadWithTermFlag BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Valid flag.
   bool mValidFlag;

   // Device names.
   char mPru30DeviceName[40];
   char mPru31DeviceName[40];

   // File descriptor.
   int mReadFd;
   int mEventFd;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   PruRxThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods, thread base class overloads:

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running. It configures the sockets.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class for the main 
   // thread processing. Execute a while loop that does read calls.
   // The loop exits when the thread is canceled.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated.
   void threadExitFunction() override;

   // Thread shutdown function. This is called in the context of the parent
   // thread. Set the termination flag, close the socket and wait for the
   // thread to terminate.
   void shutdownThread() override; 
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _AXPRURXTHREAD_CPP_
PruRxThread* gPruRxThread;
#else
extern PruRxThread* gPruRxThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

