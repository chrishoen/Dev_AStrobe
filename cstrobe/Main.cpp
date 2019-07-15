
#include "stdafx.h"

#include "risThreadsProcess.h"
#include "MainInit.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "cxStrobeParms.h"
#include "cxStrobeThread.h"

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

   if (CX::gStrobeParms.mStrobeEnable)
   {
      CX::gStrobeThread = new CX::StrobeThread;
      CX::gStrobeThread->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (CX::gStrobeThread)   CX::gStrobeThread->showThreadInfo();

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

   if (CX::gStrobeThread)
   {
      CX::gStrobeThread->shutdownThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delete program threads.

   if (CX::gStrobeThread)
   {
      delete CX::gStrobeThread;
      CX::gStrobeThread = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // End program.

   main_finalize();
   return 0;
}
