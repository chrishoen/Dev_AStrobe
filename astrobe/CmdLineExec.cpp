#include "stdafx.h"


#include "pthread.h"
#include "CmdLineExec.h"

#include "risThreadsThreads.h"
#include "risTimeMarker.h"

#include "axStrobeThread.h"
#include "axStrobeParms.h"
#include "axPruHello.h"
#include "pruShare.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("TP"))     executeTP(aCmd);
   if (aCmd->isCmd("TEST"))   executeTest(aCmd);
   if (aCmd->isCmd("HELLO"))  executeHello(aCmd);
   if (aCmd->isCmd("RP"))     executeReadPru(aCmd);
   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("Parms"))  executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTP(Ris::CmdLineCmd* aCmd)
{
   AX::gStrobeThread->mTPFlag=aCmd->argBool(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest(Ris::CmdLineCmd* aCmd)
{
   AX::gStrobeThread->mTestCode=aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeHello(Ris::CmdLineCmd* aCmd)
{
   AX::doPruHello(); 
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeReadPru(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "PruShare N1 %d", gPruShare->mN1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1 (Ris::CmdLineCmd* aCmd)
{
   Prn::print(Prn::View11, "GO1");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   AX::gStrobeParms.show();
}



