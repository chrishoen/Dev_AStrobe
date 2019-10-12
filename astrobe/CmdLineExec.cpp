#include "stdafx.h"


#include "pthread.h"
#include "CmdLineExec.h"

#include "risThreadsThreads.h"
#include "risTimeMarker.h"

#include "axStrobeThread.h"
#include "axStrobeParms.h"
#include "axPruHello.h"
#include "pruShare.h"
//test102
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
   Prn::print(0, "PruShare N2 %d", gPruShare->mN2);
   Prn::print(0, "PruShare N3 %d", gPruShare->mN3);
   Prn::print(0, "PruShare N4 %d", gPruShare->mN4);
   Prn::print(0, "PruShare U1 %u", gPruShare->mU1);
   Prn::print(0, "PruShare U2 %u", gPruShare->mU2);
   Prn::print(0, "PruShare U3 %u", gPruShare->mU3);
   Prn::print(0, "PruShare U4 %u", gPruShare->mU4);
   Prn::print(0, "PruShare U4 %u", gPruShare->mU4);

   Prn::print(0, "");
   Prn::print(0, "PruShare ArmTxMsgState %d", gPruShare->mArmTxMsgState);
   Prn::print(0, "PruShare ArmTxMsgCount %d", gPruShare->mArmTxMsgCount);
      
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
   aCmd->setArgDefaultUnsigned(1, 1);
   aCmd->setArgDefaultUnsigned(2, 0xffffffff);

   unsigned tU1 = aCmd->argUnsigned(1);
   unsigned tU2 = aCmd->argUnsigned(2);
   unsigned tDelta = tU1 - tU2;

   Prn::print(0, "U1    %8x %u", tU1, tU1);
   Prn::print(0, "U2    %8x %u", tU2, tU2);
   Prn::print(0, "Delta %u", tDelta,tDelta);
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



