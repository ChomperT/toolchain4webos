/* trampoline_r.h.  Generated from trampoline_r.h.in by configure.  */
#ifndef _TRAMPOLINE_R_H
#define _TRAMPOLINE_R_H

/*
 * Copyright 1995-1999, 2005 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#if !defined(LIBFFCALL_VERSION)
# define LIBFFCALL_VERSION 0x010B
#endif

#ifdef __cplusplus
typedef int (*__TR_function) (...);
#else
typedef int (*__TR_function) ();
#endif
extern __TR_function alloc_trampoline_r (__TR_function, void*, void*);
extern void free_trampoline_r (__TR_function);
extern int is_trampoline_r (void*);
extern __TR_function trampoline_r_address (void*);
extern void* trampoline_r_data0 (void*);
extern void* trampoline_r_data1 (void*);

#endif /* _TRAMPOLINE_R_H */
