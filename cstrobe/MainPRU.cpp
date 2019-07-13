#include "stdafx.h"

#include "risThreadsProcess.h"

#include "prussdrv.h"
#include "pruss_intc_mapping.h"

#define PRU_NUM 	0

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize pru resources.

void pru_initialize()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

   int tRet = 0;

   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

   tRet = prussdrv_init();
   printf("prussdrv_init          %d\n", tRet);

   tRet = prussdrv_open(PRU_EVTOUT_0);
   printf("prussdrv_open          %d\n", tRet);

   tRet = prussdrv_pruintc_init(&pruss_intc_initdata);
   printf("prussdrv_pruintc_init  %d\n", tRet);

   tRet = prussdrv_exec_program(PRU_NUM, "./pru/PRU_gpioToggle.out");
   printf("prussdrv_exec_program  %d\n", tRet);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize pru resourcs.

void pru_finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
