#include "stdafx.h"

#include "risThreadsProcess.h"

#include "risBaseDir.h"
#include "risPortableCalls.h"
#include "axStrobeParms.h"
#include "pruShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("AStrobe Program********************************************BEGIN\n");
   printf("AStrobe Program********************************************BEGIN\n");
   printf("AStrobe Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set program directory.

   // Set the base directory global variable to the cproc directory path.
   Ris::setBaseDirectory("/opt/aproc");

   // Set the program working directory to the cproc directory path.
   Ris::chdirToBaseDirectory();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set program process for high priority.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("AStrobe");
   TS::setProgramLogFilepath("log/AStrobeLog.txt");
   TS::setProgramPrintLevel(TS::PrintLevel(0, 3));
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   // Read parameters files.
   AX::gStrobeParms.reset();
   AX::gStrobeParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   // Initialize pru shared memory.
   Pru::gShare.initialize();

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
   printf("AStrobe Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
