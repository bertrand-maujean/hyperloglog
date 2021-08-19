/*
    hyperloglog tiny library for C++
    Copyright (C) 2021 Bertrand Maujean

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * hyperloglog.cpp
 *
 *  Created on: 5 juin 2021
 *      Author: ber
 */

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cmath>
#include "hyperloglog.h"


hyperLogLog_c::hyperLogLog_c(int nbBits_) {
	nbBits      = nbBits_;
	double alpha;

	nbRegisters = 1<<nbBits;
	switch (nbRegisters) {
		case  16: alpha=0.673; break;
		case  32: alpha=0.697; break;
		case  64: alpha=0.709; break;
		case 128:
		case 256:
		case 512:
		case 1024:
		case 2048:
		case 4096:
			alpha=1.079/((double)nbRegisters);
			alpha=alpha+1.0;
			alpha=0.7213/alpha;
			break;

		default:
			/* Cas d'erreur à gérer : nbBits incorrect */
			assert(0);
	}

	alpham2     = alpha*(double)nbRegisters*(double)nbRegisters;
	reg    		= (uint64_t*)malloc(nbRegisters * sizeof(uint64_t));
	memset(reg, 0, nbRegisters * sizeof(uint64_t));
	rightMask   = (1UL << nbBits)-1; /* masque pour le n° du registre à MàJ */
}


void hyperLogLog_c::clear() {
	memset(reg, 0, nbRegisters * sizeof(uint64_t));
}


hyperLogLog_c::~hyperLogLog_c() {
	if (reg) free(reg);
	return;
}

void hyperLogLog_c::addElement(uint64_t h) {
	uint64_t nReg = h & rightMask;
	uint64_t nZ;

	/* Il existe une instruction X86 toute faite pour compter les leading zero */
	__asm__("movq     %1, %%rax     ;"
			"lzcnt    %%rax, %%rax  ;"
			"movq     %%rax, %0     ;"
			: "=m" (nZ)
			: "m"  (h)
	);
	if (reg[nReg]<nZ) reg[nReg] = nZ;
}

void hyperLogLog_c::addElement(char*, size_t) {
	return;
}

int64_t hyperLogLog_c::count() {
	if (reg) {
		double mh = 0.0; /* moyenne harmonique */
		for (int n=0; n<nbRegisters; n++) {
			uint64_t k = (1UL <<reg[n]);
			mh = mh + (1.0/((double)k));
		}
		mh = (1.0)/mh;
		double e=alpham2*mh;
		if (e>2.5*nbRegisters) {
			return (int64_t)e;
		} else {
			int nbZ=0;
			for (int n=0; n<nbRegisters; n++) {
				if (reg[n] == 0) nbZ++;
			}
			if (nbZ == 0) {
				return (int64_t)e;
			} else {
				return (int64_t)(nbRegisters*log((double)nbRegisters/(double)nbZ));
			}
		}
	} else {
		return -1;
	}

}

