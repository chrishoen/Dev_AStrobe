/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>

#include "cxPruHello.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

#define MAX_BUFFER_SIZE 512
char readBuf[MAX_BUFFER_SIZE];
#define DEVICE_NAME0 "/dev/rpmsg_pru30"
#define DEVICE_NAME1 "/dev/rpmsg_pru31"

int doPruHello()
{
   struct pollfd pollfds;
   int result = 0;

   int pru_data;

   /* Open the rpmsg_pru character device file */
   printf("opening    %s\n", DEVICE_NAME0);
   pollfds.fd = open(DEVICE_NAME0, O_RDWR);
   /*
   * If the RPMsg channel doesn't exist yet the character device
   * won't either.
   * Make sure the PRU firmware is loaded and that the rpmsg_pru
   * module is inserted.
   */
   if (pollfds.fd < 0) {
      printf("open error %d\n", pollfds.fd);
      return -1;
   }
   else
   {
      printf("opened\n");
   }

   /* Send 'hello world!' to the PRU through the RPMsg channel */
   result = write(pollfds.fd, "hello world_0!", 13);
   printf("write      %d\n", result);

   /* Poll until we receive a message from the PRU and then print it */
   printf("reading\n");
   result = read(pollfds.fd, readBuf, MAX_BUFFER_SIZE);
   if (result > 0)
   {
      printf("Message    %s\n\n", readBuf);
   }
   else
   {
      printf("read error %d\n", result);
   }

   /* Close the rpmsg_pru character device file */
   close(pollfds.fd);
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace