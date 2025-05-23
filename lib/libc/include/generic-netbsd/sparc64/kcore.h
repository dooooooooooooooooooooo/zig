/*	$NetBSD: kcore.h,v 1.7 2008/04/28 20:23:37 martin Exp $	*/

/*-
 * Copyright (c) 1996 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Paul Kranenburg.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * The layout of a kernel core on the dump device is as follows:
 *	a `struct kcore_seg' of type CORE_CPU
 *	a `struct cpu_kcore_hdr'
 */

struct cpu_kcore_4mbseg {
	uint64_t	va;		/* virtual address */
	uint64_t	pa;		/* physical address */
};

typedef struct cpu_kcore_hdr {
	int		cputype;	/* CPU type associated with this dump */

	int		nmemseg;	/* # of physical memory segments */
	uint64_t	memsegoffset;	/* start of memseg array (relative */
					/*  to the start of this header) */

	int		nsegmap;	/* # of kernel segs */
	uint64_t	segmapoffset;	/* start of segmap array (relative */
					/*  to the start of this header) */

	uint64_t	kernbase;	/* copy of KERNBASE goes here */
	uint64_t	cpubase;	/* Pointer to cpu_info structure */

	uint64_t	ktextbase;	/* Virtual start of text segment */
	uint64_t	ktextp;		/* Physical address of 4MB locked TLB */
	uint64_t	ktextsz;	/* Size of locked kernel text segment. */

	uint64_t	kdatabase;	/* Virtual start of data segment */
	uint64_t	kdatap;		/* Physical address of 4MB locked TLB */
	uint64_t	kdatasz;	/* Size of locked kernel data segment. */

	uint64_t	newmagic;	/* magic value: everything beyound is
					   valid */
#define	SPARC64_KCORE_NEWMAGIC	0x3AFEC01E
	uint64_t	num4mbsegs;	/* number of 4MB segments */
	uint64_t	off4mbsegs;	/* start of 4m segment array
					   (relative to start of this
					   header) */

	uint64_t	numcpuinfos;	/* number of per CPU mapping infos */
	uint64_t	percpusz;	/* size of per cpu mapping */
	uint64_t	thiscpu;	/* index of the cpu writing the dump */
	uint64_t	cpusp;		/* physical address of first per-cpu
					   mapping */
} cpu_kcore_hdr_t;