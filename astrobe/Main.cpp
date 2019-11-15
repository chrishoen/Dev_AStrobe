
#include "stdafx.h"

#include "risThreadsProcess.h"
#include "MainInit.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "axStrobeParms.h"
#include "axStrobeThread.h"
#include "axPruRxThread.h"
// git test 201
//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Begin program.

   main_initialize(argc, argv);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   if (AX::gStrobeParms.mStrobeEnable)
   {
      AX::gStrobeThread = new AX::StrobeThread;
      AX::gStrobeThread->launchThread();
   }

   if (AX::gStrobeParms.mPruRxEnable)
   {
      AX::gPruRxThread = new AX::PruRxThread;
      AX::gPruRxThread->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (AX::gStrobeThread)   AX::gStrobeThread->showThreadInfo();
   if (AX::gPruRxThread)    AX::gPruRxThread->showThreadInfo();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute console command line executive, wait for user to exit.

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program threads.

   if (AX::gStrobeThread)
   {
      AX::gStrobeThread->shutdownThread();
   }

   if (AX::gPruRxThread)
   {
      AX::gPruRxThread->shutdownThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delete program threads.

   if (AX::gStrobeThread)
   {
      delete AX::gStrobeThread;
      AX::gStrobeThread = 0;
   }

   if (AX::gPruRxThread)
   {
      delete AX::gPruRxThread;
      AX::gPruRxThread = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // End program.

   main_finalize();
   return 0;
}
