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

#ifndef __RVS_IPOINT_HPP__
#define __RVS_IPOINT_HPP__

/* Macro to indicate that RVS is on */
#define RVS

/* Instrumentation point */
extern "C" {
  void RVS_Ipoint(unsigned int);
  void RVS_Init(void);
  void RVS_Output(void);
}
/* Instrumentation macros */
#define RVS_I(_I)     RVS_Ipoint(_I)
#define RVS_E(_I,_E)  (RVS_I(_I),_E)
#define RVS_C(_I,_C)  (RVS_E(_I,0)?_C:_C)
#define RVS_T(_I)     RVS_E(_I,1)
#define RVS_F(_I)     RVS_E(_I,0)

#endif

