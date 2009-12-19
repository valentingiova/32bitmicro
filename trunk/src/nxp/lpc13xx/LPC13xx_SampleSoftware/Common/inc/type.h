/*****************************************************************************
 *   type.h:  Type definition Header file for NXP Family 
 *   Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.04.01  ver 1.00    Preliminary version, first Release
 *
******************************************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

/* exact-width signed integer types */
#if !__int8_t_defined
typedef   signed          char int8_t;
#endif
#if !__int16_t_defined
typedef   signed short     int int16_t;
#endif
#if !__int32_t_defined
typedef   signed           int int32_t;
#endif
#if !__int64_defined
#if defined(__GNUC__)
#if !__int64_t_defined
typedef   signed long  int64_t;
#endif
#else
typedef   signed       __int64 int64_t;
#endif
#endif

/* exact-width unsigned integer types */
#if !__int8_t_defined
typedef unsigned          char uint8_t;
#endif
#if !__int16_t_defined
typedef unsigned short     int uint16_t;
#endif
#if !__int32_t_defined
typedef unsigned           int uint32_t;
#endif
#if !__int64_defined
#if defined(__GNUC__)
#if !__int64_t_defined
typedef   unsigned long   uint64_t;
#endif
#else
typedef unsigned       __int64 uint64_t;
#endif
#endif

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#endif  /* __TYPE_H__ */
