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
#include <sys/eventfd.h>
#include <sys/ioctl.h>


#include "risProgramTime.h"
#include "cmnPriorities.h"
#include "axStrobeParms.h"


#define  _AXPRURXTHREAD_CPP_
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
   BaseClass::setThreadPrintLevel(gStrobeParms.mPruRxPrintLevel);
   BaseClass::setThreadPriority(Cmn::gPriorities.mPruRx);

   // Set member variables.
   mValidFlag = false;
   strcpy(mPru30DeviceName, "/dev/rpmsg_pru30");
   strcpy(mPru31DeviceName, "/dev/rpmsg_pru31");
   mReadFd = 0;
   mEventFd = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It configures the socket.

void PruRxThread::threadInitFunction()
{
   int tRet = 0;
   int tSeqNum = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Open the port.

   // Open the rpmsg_pru character device file.
   mReadFd = open(mPru30DeviceName, O_RDWR);

   if (mReadFd < 0) {
      TS::print(0, "read open error %d", mReadFd);
      return;
   }
   else
   {
      TS::print(0, "read opened");
   }

   //***************************************************************************
   //***************************************************************************
   //**************************************************************************
   // Open the port.

   mEventFd = eventfd(0, EFD_SEMAPHORE);

   if (mEventFd < 0)
   {
      TS::print(1, "ERROR101 %d", errno);
      return;
   }

   //***************************************************************************
   //***************************************************************************
   //**************************************************************************
   // Send first message.

   tRet = write(mReadFd, &tSeqNum, 4);
   TS::print(0, "write      %d", tRet);

   // Done.
   mValidFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class for the main 
// thread processing. Execute a while loop that does read calls.
// The loop exits when the thread is canceled.

void PruRxThread::threadRunFunction()
{
   // Guard.
   if (!mValidFlag) return;
      
   int tRet = 0;
   int tSeqNum = 0;

   while (true)
   {
      if (BaseThreadWithTermFlag::mTerminateFlag) break;

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Poll the port for a read or a close.

      // Read.
      TS::print(5, "prurx_poll_start");

      struct pollfd tPollFd[2];
      tPollFd[0].fd = mReadFd;
      tPollFd[0].events = POLLIN;
      tPollFd[0].revents = 0;
      tPollFd[1].fd = mEventFd;
      tPollFd[1].events = POLLIN;
      tPollFd[1].revents = 0;

      // Poll the port for read.
      tRet = poll(&tPollFd[0], 2, -1);

      // Test the valid flag for closing.
      if (!mValidFlag)
      {
         TS::print(1, "prurx_poll_invalid close");
         return;
      }

      // Test the return code for error.
      if (tRet < 0)
      {
         TS::print(1, "prurx_poll_error_1 %d", errno);
         return;
      }

      // Test the return code for timeout.
      if (tRet == 0)
      {
         TS::print(1, "prurx_poll_error_2 timeout");
         return;
      }

      if (tPollFd[0].revents & POLLIN)
      {
         TS::print(5, "prurx_poll_event0 %d %04X", tRet, tPollFd[0].revents);
      }

      if (tPollFd[1].revents & POLLIN)
      {
         TS::print(5, "prurx_poll_event1 %d %04X", tRet, tPollFd[1].revents);
         return;
      }

      // Test the return code for closed port.
      if (tRet == 2)
      {
         TS::print(1, "prurx_poll_error_3 close");
         return;
      }

      TS::print(5, "prurx_poll_pass %d", tRet);

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Read from port.

      // Read.
      TS::print(5, "serial_read_start");
      tRet = (int)read(mReadFd, &tSeqNum, 4);

      // Test the return code.
      if (tRet < 0)
      {
         TS::print(0, "prurx_read_error_1 %d", errno);
         return;
      }

      TS::print(5, "prurx_read_pass %d",tRet);
      doProcessRxFrame(tSeqNum);

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Done.
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

   // Guard.
   if (!mValidFlag) return;

   BaseClass::mTerminateFlag = true;

   int tRet = 0;

   // Write bytes to the event semaphore.
   unsigned long long tCount = 1;
   tRet = write(mEventFd, &tCount, 8);

   // Close the port.
   tRet = close(mReadFd);

   // Test the return code.
   if (tRet != 0)
   {
      TS::print(1, "close_error_1 %d", errno);
   }

   // Done.
   mReadFd = 0;
   mValidFlag = false;

   // Wait for thread terminate.
   BaseClass::waitForThreadTerminate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

