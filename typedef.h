/*
 * File:	typedef.h
 * Author:	Kevin Ren <kinreven@gmail.com>
 * Brief:	This file is a common type define header file.
 *
 * $Date:: 2011-12-10 23:26:55 #$
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__


typedef char				int8_t;
typedef unsigned char		uint8_t;
typedef short				int16_t;
typedef unsigned short		uint16_t;
typedef long 				int32_t;
typedef unsigned long 		uint32_t;

/*
typedef uint32_t			size_t;
typedef uint32_t			off_t;
*/

#define TRUE				1
#define FALSE				0

#define SUCCESS				0
#define FAIL				1		

/*
#define UINT8_MAX			0xff
#define UINT16_MAX			0xffff
#define UINT32_MAX			0xffffffff

#define NULL				((void *)0)
*/

#endif /*__TYPEDEF_H__*/
