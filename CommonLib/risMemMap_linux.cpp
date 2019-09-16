/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "risPortableCalls.h"

#include "risMemMap.h"

namespace Ris
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// Max string size used in subsequent calls.
static const int cPageSize = 4096;

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Instruct the OS kernel to map a physical address to a virtual address.
// Return the virtual address.

void* getMemMapVirtualAddress(void* aPhysicalAddress, int aNumPages)
{
   // Calculate the size of memory to allocate.
   size_t tLength = cPageSize * aNumPages;
   unsigned tMask = tLength - 1;
   off_t tPhysicalAddress = (off_t)aPhysicalAddress & (off_t)~tMask;

   // Open a file to the memory system.
   int tMemoryFd = open("/dev/mem", O_RDWR | O_SYNC);

   void* tVirtualAddress = mmap(0, tLength, PROT_READ | PROT_WRITE, MAP_SHARED, tMemoryFd, tPhysicalAddress);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

