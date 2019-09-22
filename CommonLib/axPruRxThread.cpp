/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>

#include "prnPrint.h"
#include "risThreadsPriorities.h"
#include "axPruRxThread.h"

namespace AX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PruRxThread::PruRxThread()
{
   // Set base class variables.
   BaseClass::setThreadName("PruRx");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mNormal);
   BaseClass::setThreadPrintLevel(TS::PrintLevel(0,3));

   // Set member variables.
   strcpy(mPru30DeviceName, "/dev/rpmsg_pru30");
   strcpy(mPru31DeviceName, "/dev/rpmsg_pru31");
   mPollFds.fd = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It configures the socket.

void PruRxThread::threadInitFunction()
{
   int result = 0;

   int pru_data;

   /* Open the rpmsg_pru character device file */
   TS::print(0,"opening    %s\n", mPru30DeviceName);
   mPollFds.fd = open(mPru30DeviceName, O_RDWR);

   /*
   * If the RPMsg channel doesn't exist yet the character device
   * won't either.
   * Make sure the PRU firmware is loaded and that the rpmsg_pru
   * module is inserted.
   */
   if (mPollFds.fd < 0) {
      TS::print(0, "open error %d\n", mPollFds.fd);
      return;
   }
   else
   {
      TS::print(0, "opened\n");
   }

   /* Send 'hello world!' to the PRU through the RPMsg channel */
   result = write(mPollFds.fd, "hello world_0!", 13);
   TS::print(0, "write      %d\n", result);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class for the main 
// thread processing. Execute a while loop that does read calls.
// The loop exits when the thread is canceled.

void  PruRxThread::threadRunFunction()
{
   bool tGoing = true;
   bool tFirstFlag = true;

   while (tGoing)
   {
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated.

void PruRxThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This is called in the context of the parent
// thread. Set the termination flag, close the socket and wait for the
// thread to terminate.
//
// If the while loop in the threadRunFunction is blocked on doReceiveString then
// closing the socket will cause doReceiveString to return with false and 
// then the terminate request flag will be polled and the threadRunFunction 
// will exit.

void PruRxThread::shutdownThread()
{
   shutdownThreadPrologue();
   BaseThreadWithTermFlag::mTerminateFlag = true;

   close(mPollFds.fd);

   BaseThreadWithTermFlag::waitForThreadTerminate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

