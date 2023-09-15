/*
--  ===========================================================================
--  Rapita Systems Ltd. - Rapita Verification Suite (RVS) Source Code License
--
--  DOC13027 V1 (2014/01/28)
--
--  (c) 2004-2018 Rapita Systems Ltd. All rights reserved
--  ---------------------------------------------------------------------------
--
--  Subject to the terms and conditions of the RVS License Agreement, Rapita
--  Systems Ltd. grants the Licensee a non-exclusive, non-transferable license
--  to use the source code contained in this file (the "Licensed Software").
--
--  The Licensee may use the Licensed Software for its own use, and may
--  translate or modify it or incorporate it into other software. The Licensee
--  may not, however, alter or remove the copyright notice or the text of the
--  source code license.
--
--  The Licensee may not, however, transfer or sublicense the Licensed Software
--  to any third party, in whole or in part, in any form, whether modified or
--  unmodified without the prior written consent of Rapita Systems Ltd.
--
--  The original and any copies of the Licensed Software, made by the Licensee,
--  including translations, compilations, partial copies, modifications,
--  and updates, are the property of Rapita Systems Ltd.
--
--  The Licensee recognizes that Rapita Systems Ltd. regards the Licensed
--  Software as its proprietary information and as confidential trade secrets.
--
--  The Licensee agrees not to provide or to otherwise make available in any
--  form the Licensed Software, or any portion thereof, to any person other
--  than employees of the Licensee without the prior written consent of
--  Rapita Systems Ltd.
--
--  The Licensee further agrees to treat the Licensed Programs with at least
--  the same degree of care with which the Licensee treats its own confidential
--  information and in no event with less care than is reasonably required to
--  protect the confidentiality of the Licensed Software.
--
--
--  Registered in the UK, number 5011090
--  Registered address:
--   Atlas House, Link Business Park
--   Osbaldwick Link Road
--   York
--   YO10 3JB
--   UK
--  Phone: +44 (0) 1904 413 945
--
--  email: support@rapitasystems.com
--  http://www.rapitasystems.com/
--
--  ===========================================================================
*/


#ifndef __RVS_TYPES_H__
#define __RVS_TYPES_H__

typedef unsigned char      t_rvs_uint8;
typedef t_rvs_uint8      * t_rvs_uint8_ptr;
typedef unsigned int       t_rvs_uint32;
typedef t_rvs_uint32     * t_rvs_uint32_ptr;
typedef unsigned long long t_rvs_uint64;
typedef signed long long   t_rvs_int64;
typedef unsigned char      t_rvs_boolean;
typedef unsigned int       t_rvs_size_t;
#define RVS_FALSE 0
#define RVS_TRUE (!RVS_FALSE)
#define RVS_NULL ((void *)0)
typedef struct {t_rvs_uint32 T[2];} t_rvs_2_uint32;
typedef struct {t_rvs_uint32 T[4];} t_rvs_4_uint32;

/* These are the largest integers RVS can handle in calculations */
typedef t_rvs_uint64 t_rvs_ulong;
typedef t_rvs_int64  t_rvs_slong;

/* This can be anything up to and including 64 bits */
typedef unsigned long long int t_rvs_test_id;

#endif
