/*
 * (C) Copyright 1992, ..., 2014 the "DOSEMU-Development-Team".
 *
 * for details see file COPYING in the DOSEMU distribution
 */

#ifndef __HMA_H
#define __HMA_H

extern int a20;
extern unsigned char *ext_mem_base;
void set_a20(int);
void extmem_copy(unsigned dst, unsigned src, unsigned len);

#endif
