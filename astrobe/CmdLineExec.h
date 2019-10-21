#pragma once

#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeTP      (Ris::CmdLineCmd* aCmd);
  void executeHello   (Ris::CmdLineCmd* aCmd);
  void executeTest    (Ris::CmdLineCmd* aCmd);
  void executeReadPru (Ris::CmdLineCmd* aCmd);
  void executeGo1     (Ris::CmdLineCmd* aCmd);
  void executeGo2     (Ris::CmdLineCmd* aCmd);
  void executeGo3     (Ris::CmdLineCmd* aCmd);
  void executeTN1     (Ris::CmdLineCmd* aCmd);
  void executeTN2     (Ris::CmdLineCmd* aCmd);

  void executeParms   (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

