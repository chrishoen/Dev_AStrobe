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
   BaseClass::setThreadPrintLevel(gStrobeParms.mStrobePrintLevel);
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
   int result = 0;

   int pru_data;

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

   result = write(mReadFd, "hello world_0!", 13);
   TS::print(0, "write      %d", result);

   // Done.
   mValidFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class for the main 
// thread processing. Execute a while loop that does read calls.
// The loop exits when the thread is canceled.

void  PruRxThread::threadRunFunction()
{
   // Guard.
   if (!mValidFlag) return;
      
   char tReadBuf[512];
   int tResult = 0;

   while (true)
   {
      if (BaseThreadWithTermFlag::mTerminateFlag) break;

      tResult = read(mReadFd, tReadBuf, 512);
      if (tResult > 0)
      {
         Prn::print(Prn::View11, "RxMessage %s",tReadBuf);
      }
      else
      {
         Prn::print(Prn::View11, "RxMessage Error %d", tResult);
         return;
      }
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

