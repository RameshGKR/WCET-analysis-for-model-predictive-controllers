/* RVS - RapiTime - C Instrumentation library */

/*=============================================================================
* Rapita Systems Ltd. - Rapita Verification Suite (RVS) Source Code License
*
* DOC13027 V1 (2014/01/28)
*
* (c) 2004-2018 Rapita Systems Ltd. All rights reserved
* -----------------------------------------------------------------------------
*
* Subject to the terms and conditions of the RVS License Agreement, Rapita
* Systems Ltd. grants the Licensee a non-exclusive, non-transferable license to
* use the source code contained in this file (the "Licensed Software").
*
* The Licensee may use the Licensed Software for its own use, and may
* translate or modify it or incorporate it into other software. The Licensee 
* may not, however, alter or remove the copyright notice or the text of the
* source code license.
*
* The Licensee may not, however, transfer or sublicense the Licensed Software
* to any third party, in whole or in part, in any form, whether modified or
* unmodified without the prior written consent of Rapita Systems Ltd.
*
* The original and any copies of the Licensed Software, made by the Licensee,
* including translations, compilations, partial copies, modifications,
* and updates, are the property of Rapita Systems Ltd.
*
* The Licensee recognizes that Rapita Systems Ltd. regards the Licensed
* Software as its proprietary information and as confidential trade secrets.
*
* The Licensee agrees not to provide or to otherwise make available in any
* form the Licensed Software, or any portion thereof, to any person other
* than employees of the Licensee without the prior written consent of
* Rapita Systems Ltd.
*
* The Licensee further agrees to treat the Licensed Programs with at least
* the same degree of care with which the Licensee treats its own confidential
* information and in no event with less care than is reasonably required to
* protect the confidentiality of the Licensed Software.
*
* -----------------------------------------------------------------------------
*
* Registered in the UK, number 5011090.
* Registered address:
*   Atlas House, Link Business Park
*   Osbaldwick Link Road
*   York
*   YO10 3JB
*   UK
* Phone: +44 (0) 1904 413 945
* 
* email: support@rapitasystems.com
* http://www.rapitasystems.com/
*
*=============================================================================
*/ 

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "rvs.h"
#include "rvs_ipoint.h"
#include "gpio_defs.h"

/* Number of times a value should be correct before continuing */
#define POLL_COUNT 3

/**************************************************************
 * delay_us: wait for us microseconds
 **************************************************************/
void delay_us(unsigned int us)
{
    volatile uint32_t * time = (uint32_t *) SYS_TIMER_CLO;
    uint32_t start = *time;
    while (*time - start <= us);
}

/**************************************************************
 * gpio_fsel: set GPIO pin mode
 **************************************************************/
void gpio_fsel(int pin, int mode)
{
    volatile uint32_t *reg = (uint32_t *) GPIO_FSEL + (pin / 10);
    uint8_t shift = (pin % 10) * 3;

    *reg = (*reg & ~(7 << shift)) | (mode << shift);
}

/**************************************************************
 * Instrumentation point
 **************************************************************/
void RVS_Ipoint(unsigned int id)
{
  volatile uint32_t* reg;

  /* Assert enable (GPIO 23) and set ID (GPIO 0-13) + odd parity (GPIO 16) */
  reg = (uint32_t*) GPIO_CLR0;
  *reg = GPIO_MASK_16 | GPIO_MASK_13_0;
  reg = (uint32_t*) GPIO_SET0;
  *reg = GPIO_MASK_23 | (__builtin_parity(GPIO_MASK_13_0 & id) << 16) | (GPIO_MASK_13_0 & id);

  /* Poll for acknowledge (GPIO 26) assert */
  reg = (uint32_t*) GPIO_LEV0;
  for (int i = 0; i < POLL_COUNT-1; i++)
  {
    if (!(*reg & GPIO_MASK_26)) i = 0;
  }

  /* Clear enable (GPIO 23) */
  reg = (uint32_t*) GPIO_CLR0;
  *reg = GPIO_MASK_23;

  /* Poll for acknowledge (GPIO 26) clear */
  reg = (uint32_t*) GPIO_LEV0;
  for (int i = 0; i < POLL_COUNT-1; i++)
  {
    if (*reg & GPIO_MASK_26) i = 0;
  }
}

/*************************************************************
 * RVS_Init: Initialise the instrumentation library
 *************************************************************/
void RVS_Init (void)
{
  volatile uint32_t* reg;

  /* CONFIGURE AND INITIALIZE GPIO */
  /* Configure GPIO 0-13 & 16 & 23-25 as output */
  for (int i = 0; i <= 13; i++)
  {
      gpio_fsel(i, GPIO_FSEL_OUT);
  }
  gpio_fsel(16, GPIO_FSEL_OUT);
  gpio_fsel(23, GPIO_FSEL_OUT);
  gpio_fsel(24, GPIO_FSEL_OUT);
  gpio_fsel(25, GPIO_FSEL_OUT);

  /* Configure GPIO 26 as input */
  gpio_fsel(26, GPIO_FSEL_IN);

  /* Initialize GPIO 0-13 & 16 & 23-25 low */
  reg = (uint32_t *) GPIO_CLR0;
  *reg = GPIO_MASK_25 | GPIO_MASK_24 | GPIO_MASK_23 | GPIO_MASK_16 | GPIO_MASK_13_0;

  /* RESET COUNTER */
  /* Assert reset (GPIO 24) and enable (GPIO 23) */
  reg = (uint32_t *) GPIO_SET0;
  *reg = GPIO_MASK_24 | GPIO_MASK_23;

  /* Poll for acknowledge (GPIO 26) assert */
  reg = (uint32_t*) GPIO_LEV0;
  for (int i = 0; i < POLL_COUNT-1; i++)
  {
    if (!(*reg & GPIO_MASK_26)) i = 0;
  }

  /* Clear enable (GPIO23) and reset (GPIO 24) */
  reg = (uint32_t*) GPIO_CLR0;
  *reg = GPIO_MASK_24 | GPIO_MASK_23;

  /* Poll for acknowledge (GPIO 26) clear */
  reg = (uint32_t*) GPIO_LEV0;
  for (int i = 0; i < POLL_COUNT-1; i++)
  {
    if (*reg & GPIO_MASK_26) i = 0;
  }
}

/**************************************************************
 * RVS_Output: Output the current coverage data
 **************************************************************/
void RVS_Output (void)
{
  volatile uint32_t* reg;

  /* Assert enable (GPIO 23) and done (GPIO 25) */
  reg = (uint32_t *) GPIO_SET0;
  *reg = GPIO_MASK_25 | GPIO_MASK_23;

  /* Poll for acknowledge (GPIO 26) assert */
  reg = (uint32_t*) GPIO_LEV0;
  for (int i = 0; i < POLL_COUNT-1; i++)
  {
    if (!(*reg & GPIO_MASK_26)) i = 0;
  }

  /* Clear enable (GPIO 23) and done (GPIO 25) */
  reg = (uint32_t *) GPIO_CLR0;
  *reg = GPIO_MASK_25 | GPIO_MASK_23;

  /* Poll for acknowledge (GPIO 26) clear */
  reg = (uint32_t*) GPIO_LEV0;
  for (int i = 0; i < POLL_COUNT-1; i++)
  {
    if (*reg & GPIO_MASK_26) i = 0;
  }
}

/**************************************************************
 * RVS_Build_Id: Set the build id for the instrumented source code
 **************************************************************/
void RVS_Build_Id (const char* build_id)
{
  int i;

  /* 7,5 = build id */
  RVS_Ipoint(7);
  RVS_Ipoint(5);

  /* 0 terminated string : build ID */
  for (i=0 ; build_id[i]!=0 ; i++)
  {
    RVS_Ipoint(build_id[i]);
  }
  RVS_Ipoint(0);
}

/**************************************************************
 * RVS_Begin_Test: Output data for the previous test and mark the start of a new test
 **************************************************************/
void RVS_Begin_Test (unsigned int test_id, char* test_description)
{
  int i;

  /* 7,6 = coverage test event */
  RVS_Ipoint(7);
  RVS_Ipoint(6);

  /* 4 bytes for the test ID */
  RVS_Ipoint((test_id>>0) & 0xFF);
  RVS_Ipoint((test_id>>8) & 0xFF);
  RVS_Ipoint((test_id>>16) & 0xFF);
  RVS_Ipoint((test_id>>24) & 0xFF);

  /* 0 terminated string : test description*/
  for (i=0 ; test_description[i]!=0 ; i++)
  {
    RVS_Ipoint(test_description[i]);
  }
  RVS_Ipoint(0);
}
