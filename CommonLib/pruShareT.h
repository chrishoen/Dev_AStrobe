#ifndef _PRUSHARET_H_
#define _PRUSHARET_H_

/*==============================================================================
This defines a memory structure that is shared between the arm and the pru.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This defines a memory structure that is shared between the arm and the pru.

typedef struct PruShareT
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // General purpose integer variables.
   int mN1;
   int mN2;
   int mN3;
   int mN4;

   // General purpose integer variables.
   unsigned mU1;
   unsigned mU2;
   unsigned mU3;
   unsigned mU4;

   // Message variables.
   int mArmTxMsgState;
   int mArmTxMsgCount;

} PruShareT;

//****************************************************************************
//****************************************************************************
//****************************************************************************
#endif