#include "stdafx.h"

#include "risThreadsProcess.h"

#include "cisCProcDir.h"
#include "risPortableCalls.h"
#include "cxStrobeParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("CStrobe Program********************************************BEGIN\n");
   printf("CStrobe Program********************************************BEGIN\n");
   printf("CStrobe Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set program process for high priority.
   Ris::Threads::enterProcessHigh();

   // Set the program working directory to the cproc directory path.
   Cis::setProgramDirToCProc();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("CStrobe");
   TS::setProgramLogFilepath("log/CStrobeLog.txt");
   TS::setProgramPrintLevel(TS::PrintLevel(0, 3));
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   // Read parameters files.
   CX::gStrobeParms.reset();
   CX::gStrobeParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::ThreadInit1, true);
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  false);
   Prn::setFilter(Prn::ThreadRun4,  false);
   Prn::setFilter(Prn::View11,      true, 1);
   Prn::setFilter(Prn::View12,      false, 1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resourcs.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // Done.
   printf("\n");
   printf("CStrobe Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
